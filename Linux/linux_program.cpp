#include <linuxprogram.h>
#include <iostream>

LinuxProgram::LinuxProgram() {
	p_joystick = new LinuxJoystick();
	p_joystick->initialize();
	pthread_create(&_jsStateThread, NULL, &LinuxProgram::getJoystickState, this);
}

LinuxProgram::~LinuxProgram() {
	Program::isRunning = false;
	pthread_join(_jsStateThread, NULL);
	pthread_cancel(_jsStateThread);
}

LinuxJoystick* LinuxProgram::getJoystick() const {
	return dynamic_cast<LinuxJoystick*>(p_joystick);
}

void* LinuxProgram::getJoystickState(void* obj) {
	Joystick* js = reinterpret_cast<LinuxProgram*>(obj)->getJoystick();
	KeyMapping* keyMap = reinterpret_cast<LinuxProgram*>(obj)->getKeyMap();

	while (Program::isRunning) {
		js->fillState();
		Joystick_State state = js->getCurrentState();
		KeyboardButton kb;

		if (js->isButtonPressed(ControllerButtons::DPAD_LEFT)) {
			std::cout << "Left dpad pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::DPAD_RIGHT)) {
			std::cout << "Right dpad pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::DPAD_UP)) {
			std::cout << "Up dpad pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::DPAD_DOWN)) {
			std::cout << "Down dpad pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::A_BUTTON)) {
			kb = keyMap->getKeyboardButtonFor(ControllerButtons::A_BUTTON);
			std::cout << "A button maps to '" << kb << "'" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::B_BUTTON)) {
			kb = keyMap->getKeyboardButtonFor(ControllerButtons::B_BUTTON);
			std::cout << "B button maps to '" << kb << "'" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::X_BUTTON)) {
			kb = keyMap->getKeyboardButtonFor(ControllerButtons::X_BUTTON);
			std::cout << "X button maps to '" << kb << "'" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::Y_BUTTON)) {
			kb = keyMap->getKeyboardButtonFor(ControllerButtons::Y_BUTTON);
			std::cout << "Y button maps to '" << kb << "'" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::LEFT_SHOULDER_BUTTON)) {
			std::cout << "Left shoulder button pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::RIGHT_SHOULDER_BUTTON)) {
			std::cout << "Right shoulder button pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::LEFT_STICK_BUTTON)) {
			std::cout << "Left stick pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::RIGHT_STICK_BUTTON)) {
			std::cout << "Right stick pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::BACK_BUTTON)) {
			std::cout << "Back button pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::MENU_BUTTON)) {
			std::cout << "Menu button pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::HOME_BUTTON)) {
			std::cout << "Home button pressed" << std::endl;
		}
	}
}