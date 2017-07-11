#include <string>
#include <stdexcept>
#include <exception>
#include <consolelogger.h>
#include <filelogger.h>
#include <settings.h>
#include <keymapping.h>
#include <keybindconverter.h>

#if PLATFORM_LINUX
#include <linuxjoystick.h>
#include <linuxkeyboard.h>
#include <csignal>
#elif PLATFORM_WINDOWS
#include <windowsjoystick.h>
#include <windowskeyboard.h>
#include <windows.h>
#endif

#define safe_delete(ptr) if(ptr) { delete ptr; ptr = NULL; }

// Forward-declared method signatures
KeyMapping buildKeyMap(std::string fileLocation);
Joystick* createJoystick(MessageLogger* pLogger);
Keyboard* createKeyboard(MessageLogger* pLogger);
void sleep(int sleepMs);
void setupSignalHandler();

// Globals
Joystick* joystick = NULL;
Keyboard* keyboard = NULL;
bool isRunning = true;
std::string settingsFileLocation = "settings.txt";

#if PLATFORM_WINDOWS
BOOL WINAPI signalHandler(DWORD signal) { if (signal == CTRL_C_EVENT || signal == CTRL_CLOSE_EVENT) { isRunning = false; return TRUE; } return FALSE; }
#elif PLATFORM_LINUX
void signalHandler(int signalNum) { isRunning = false; }
#endif

int main (int argc, char** argv) {
	ConsoleLogger logger;
	setupSignalHandler();
	try {
		Settings settings;
		settings.load();

		std::string fileLocation = settings.getValue("keybindings_location");
		KeyMapping keyMap = buildKeyMap(fileLocation);
		keyboard = createKeyboard(&logger);
		joystick = createJoystick(&logger);

		joystick->buttonPressed = [&](ControllerButton btn) {
			keyboard->sendKeyPress(keyMap.getKeyboardButtonFor(btn));
		};
		joystick->buttonReleased = [&](ControllerButton btn) {
			keyboard->sendKeyRelease(keyMap.getKeyboardButtonFor(btn));
		};

		int connectAttempts = 0;
		joystick->connect();

		while (isRunning) {
			if (!joystick->isActive()) {
				joystick->connect();
				++connectAttempts;
			}

			if (joystick->isActive()) {
				connectAttempts = 0;
				joystick->fillState();
			}
			else if (!joystick->isActive() && connectAttempts >= 5) {
				throw std::runtime_error("Joystick connect attempt threshold met.");
			}

			sleep(25);
		}
	}
	catch (std::exception& ex) {
		logger.log(ex.what());
	}
	catch (...) {
		logger.log("Unknown exception occurred");
	}

	safe_delete(joystick);
	safe_delete(keyboard);

	return 0;
}

void setupSignalHandler() {
#if PLATFORM_WINDOWS
	SetConsoleCtrlHandler(signalHandler, TRUE);
#elif PLATFORM_LINUX
	signal(SIGHUP, signalHandler);
	signal(SIGINT, signalHandler);
#endif
}

Joystick* createJoystick(MessageLogger* pLogger) {
#if PLATFORM_WINDOWS
	return new WindowsJoystick(pLogger);
#elif PLATFORM_LINUX
	return new LinuxJoystick(pLogger);
#else
	throw std::runtime_error("Unsupported platform");
#endif
}

Keyboard* createKeyboard(MessageLogger* pLogger) {
#if PLATFORM_WINDOWS
	return new WindowsKeyboard(pLogger);
#elif PLATFORM_LINUX
	return new LinuxKeyboard(pLogger);
#else
	throw std::runtime_error("Unsupported platform");
#endif
}

void sleep(int sleepMs) {
#if PLATFORM_WINDOWS
	Sleep(sleepMs);
#elif PLATFORM_LINUX
	usleep(sleepMs);
#endif
}

KeyMapping buildKeyMap(std::string fileLocation) {
	KeyMapping keyMap = {};
	
	ifstream inFile(fileLocation);
	if (!inFile) {
		std::string msg = "Unable to load '";
		msg.append(fileLocation);
		msg.append("'");
		throw std::runtime_error(msg.c_str());
	}

	std::string line;
	while (getline(inFile, line)) {
		if (line.length() == 0) {
			continue;
		}

		KeyBind bind = KeyBindConverter::toKeyBind(line);
		keyMap.addBinding(bind);
	}

	return keyMap;
}
