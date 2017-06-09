#include <linuxprogram.h>

LinuxProgram::LinuxProgram() {
	p_keyboard = new LinuxKeyboard();
	p_joystick = new LinuxJoystick();

	p_joystick->buttonPressed = [&](ControllerButton btn) {
		KeyboardButton* kbBtn = getKeyMap()->getKeyboardButtonFor(btn);
		p_keyboard->sendKeyPress(getKeyMap()->getKeyboardButtonFor(btn));
	};
	p_joystick->buttonReleased = [&](ControllerButton btn) {
		KeyboardButton* kbBtn = getKeyMap()->getKeyboardButtonFor(btn);
		p_keyboard->sendKeyRelease(getKeyMap()->getKeyboardButtonFor(btn));
	};
}

LinuxProgram::LinuxProgram(char* fileLocation, MessageLogger* pLogger) :
	Program(fileLocation, pLogger) {

	p_keyboard = new LinuxKeyboard();
	p_joystick = new LinuxJoystick();

	p_joystick->buttonPressed = [&](ControllerButton btn) {
		KeyboardButton* kbBtn = getKeyMap()->getKeyboardButtonFor(btn);
		p_keyboard->sendKeyPress(getKeyMap()->getKeyboardButtonFor(btn));
	};
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

void LinuxProgram::run() {
	LinuxJoystick* js = this->getJoystick();
	while(true) {
		if (!js->isActive()) {
			p_logger->log("State:  NOT ACTIVE");
			break;
		}

		js->fillState();
		usleep(25);
	}
}