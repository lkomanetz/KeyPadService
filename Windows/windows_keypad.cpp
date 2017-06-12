#include <windowskeypad.h>
#include <iostream>

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
}

WindowsKeypad::~WindowsKeypad() { }

WindowsJoystick* WindowsKeypad::getJoystick() {
	return dynamic_cast<WindowsJoystick*>(p_joystick);
}

void WindowsKeypad::run() {
	WindowsJoystick* js = this->getJoystick();
	while (true) {
		if (!js->isActive()) {
			p_logger->log("Gamepad State:  NOT ACTIVE");
			break;
		}

		js->fillState();
		Sleep(25);
	}	
}