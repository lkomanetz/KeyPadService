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
#define MAX_CONNECT_ATTEMPTS 5

// Forward-declared method signatures
KeyMapping buildKeyMap(std::string fileLocation);
Joystick* createJoystick(MessageLogger* pLogger, const Settings* pSettings);
Keyboard* createKeyboard(MessageLogger* pLogger, const Settings* pSettings);
void sleep(int sleepMs);
void setupSignalHandler();

// Globals
bool isRunning = true;
std::string settingsFileLocation = "service_settings.txt";

#if PLATFORM_WINDOWS
BOOL WINAPI signalHandler(DWORD signal) { if (signal == CTRL_C_EVENT || signal == CTRL_CLOSE_EVENT) { isRunning = false; return TRUE; } return FALSE; }
#elif PLATFORM_LINUX
void signalHandler(int signalNum) { isRunning = false; }
#endif

int main (int argc, char** argv) {
	Keyboard* pKeyboard = NULL;
	Joystick* pJoystick = NULL;
	ConsoleLogger logger;
	setupSignalHandler();

	try {
		Settings settings(settingsFileLocation.c_str());
		settings.load();

		std::string fileLocation = settings.getValue("keybindings_location");
		KeyMapping keyMap = buildKeyMap(fileLocation);
		pKeyboard = createKeyboard(&logger, &settings);
		pJoystick = createJoystick(&logger, &settings);

		pJoystick->buttonPressed = [&](ControllerButton btn) {
			pKeyboard->sendKeyPress(keyMap.getKeyboardButtonFor(btn));

		};
		pJoystick->buttonReleased = [&](ControllerButton btn) {
			pKeyboard->sendKeyRelease(keyMap.getKeyboardButtonFor(btn));
		};

		int connectAttempts = 0;
		pJoystick->connect();

		while (isRunning) {
			if (!pJoystick->isActive() && connectAttempts < MAX_CONNECT_ATTEMPTS) {
				pJoystick->connect();
				++connectAttempts;
				continue;
			}

			if (!pJoystick->isActive() && connectAttempts >= MAX_CONNECT_ATTEMPTS) {
				throw std::runtime_error("Joystick connect attempt threshold met.");
			}

			connectAttempts = 0;
			pJoystick->fillState();
			sleep(25);
		}
	}
	catch (std::exception& ex) {
		logger.log(ex.what());
	}
	catch (...) {
		logger.log("Unknown exception occurred");
	}

	safe_delete(pJoystick);
	safe_delete(pKeyboard);

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

Joystick* createJoystick(MessageLogger* pLogger, const Settings* pSettings) {
#if PLATFORM_WINDOWS
	return new WindowsJoystick(pLogger);
#elif PLATFORM_LINUX
	return new LinuxJoystick(pLogger, pSettings->getValue("joystick_port"));
#else
	throw std::runtime_error("Unsupported platform");
#endif
}

Keyboard* createKeyboard(MessageLogger* pLogger, const Settings* pSettings) {
#if PLATFORM_WINDOWS
	return new WindowsKeyboard(pLogger);
#elif PLATFORM_LINUX
	return new LinuxKeyboard(pLogger, pSettings->getValue("keyboard_port"));
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
