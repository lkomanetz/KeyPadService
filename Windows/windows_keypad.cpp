#include <windowskeypad.h>

WindowsKeypad::WindowsKeypad(char* fileLocation, MessageLogger* pLogger) :
	Program(fileLocation, pLogger) {

	p_keyboard = new WindowsKeyboard(p_logger);
	p_joystick = new WindowsJoystick(p_logger);

	p_joystick->buttonPressed = [&](ControllerButton btn) { 
		p_keyboard->sendKeyPress(getKeyMap()->getKeyboardButtonFor(btn));
	};
	p_joystick->buttonReleased = [&](ControllerButton btn) {
		p_keyboard->sendKeyRelease(getKeyMap()->getKeyboardButtonFor(btn));
	};

	this->setupSignalHandler();
}

WindowsKeypad::~WindowsKeypad() { }

WindowsJoystick* WindowsKeypad::getJoystick() {
	return dynamic_cast<WindowsJoystick*>(p_joystick);
}

void WindowsKeypad::run() {
	WindowsJoystick* js = this->getJoystick();
	js->connect();
	while (Program::isRunning) {
		if (!js->isActive()) {
			Program::isRunning = false;
			break;
		}

		js->fillState();
		this->sleep(25);
	}	
}

void WindowsKeypad::setupSignalHandler() {
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)WindowsKeypad::signalHandler, TRUE);
}

void WindowsKeypad::sleep(int sleepMs) {
	Sleep(sleepMs);
}

BOOL WINAPI WindowsKeypad::signalHandler(DWORD signal) {
	if (signal == CTRL_C_EVENT || signal == CTRL_CLOSE_EVENT) {
		Program::isRunning = false;
		return TRUE;
	}

	return FALSE;
}