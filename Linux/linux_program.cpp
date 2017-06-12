#include <linuxkeypad.h>

LinuxKeypad::LinuxKeypad() {
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

LinuxKeypad::LinuxKeypad(char* fileLocation, MessageLogger* pLogger) :
	Keypad(fileLocation, pLogger) {

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

LinuxKeypad::~LinuxKeypad() {
	Keypad::isRunning = false;
}

LinuxJoystick* LinuxKeypad::getJoystick() const {
	return dynamic_cast<LinuxJoystick*>(p_joystick);
}

void LinuxKeypad::run() {
	LinuxJoystick* js = this->getJoystick();
	while(true) {
		if (!js->isActive()) {
			p_logger->log("Gamepad State:  NOT ACTIVE");
			break;
		}

		js->fillState();
		usleep(25);
	}
}