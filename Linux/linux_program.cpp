#include <linuxprogram.h>
#include <iostream>

LinuxProgram::LinuxProgram(char* fileLocation) :
	Program(fileLocation) {

	p_keyboard = new LinuxKeyboard();
	p_joystick = new LinuxJoystick();

	//TODO(Logan) -> I need to pass multiple controller buttons that are currently pressed.
	p_joystick->buttonPressed = [&](ControllerButton btn) {
		KeyboardButton* kbBtn = getKeyMap()->getKeyboardButtonFor(btn);
		p_keyboard->sendKeyPress(getKeyMap()->getKeyboardButtonFor(btn));
	};
	//TODO(Logan) -> I need to pass multiple controller buttons that have been released.
	p_joystick->buttonReleased = [&](ControllerButton btn) {
		KeyboardButton* kbBtn = getKeyMap()->getKeyboardButtonFor(btn);
		p_keyboard->sendKeyRelease(getKeyMap()->getKeyboardButtonFor(btn));
	};
}

LinuxProgram::~LinuxProgram() {
	Program::isRunning = false;
}

LinuxJoystick* LinuxProgram::getJoystick() const {
	return dynamic_cast<LinuxJoystick*>(p_joystick);
}