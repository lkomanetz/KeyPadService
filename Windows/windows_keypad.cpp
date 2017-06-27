#include <windowskeypad.h>

WindowsKeypad::WindowsKeypad(char* fileLocation, MessageLogger* pLogger) :
	Program(fileLocation, pLogger) {

	p_keyboard = new WindowsKeyboard();
	p_joystick = new WindowsJoystick();

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
	while (Program::isRunning) {
		if (!js->isActive()) {
			p_logger->log("Gamepad State:  NOT ACTIVE");
			Program::isRunning = false;
			break;
		}

		js->fillState();
		Sleep(25);
	}	
}

void WindowsKeypad::setupSignalHandler() {
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)WindowsKeypad::signalHandler, TRUE);
}

BOOL WINAPI WindowsKeypad::signalHandler(DWORD signal) {
	if (signal == CTRL_C_EVENT || signal == CTRL_CLOSE_EVENT) {
		Program::isRunning = false;
		return TRUE;
	}

	return FALSE;
}