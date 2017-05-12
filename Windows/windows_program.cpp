#include <windowsprogram.h>
#include <iostream>

WindowsProgram::WindowsProgram(char* fileLocation) :
	Program(fileLocation) {

	p_keyboard = new WindowsKeyboard();
	p_joystick = new WindowsJoystick();

	p_joystick->buttonPressed = [&](ControllerButton btn) { 
		p_keyboard->sendKeyPress(getKeyMap()->getKeyboardButtonFor(btn));
	};
	p_joystick->buttonReleased = [&](ControllerButton btn) {
		p_keyboard->sendKeyRelease(getKeyMap()->getKeyboardButtonFor(btn));
	};
}

WindowsProgram::~WindowsProgram() { }

WindowsJoystick* WindowsProgram::getJoystick() {
	return dynamic_cast<WindowsJoystick*>(p_joystick);
}