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

	while (Program::isRunning) {
		js->fillState();
		Joystick_State state = js->getCurrentState();

		for (auto it : state.buttonStates) {
			if (it.second == 1) {
				std::cout << "Button '" << it.first << "' is pressed!" << std::endl;
			}
		}

		//TODO(Logan)-> DPAD_DOWN and DPAD_RIGHT aren't working
		if (js->isButtonPressed(ControllerButtons::DPAD_LEFT))
			std::cout << "Left dpad pressed" << std::endl;
		else if (js->isButtonPressed(ControllerButtons::DPAD_RIGHT))
			std::cout << "Right dpad pressed" << std::endl;
		else if (js->isButtonPressed(ControllerButtons::DPAD_UP))
			std::cout << "Up dpad pressed" << std::endl;
		else if (js->isButtonPressed(ControllerButtons::DPAD_DOWN))
			std::cout << "Down dpad pressed" << std::endl;
	}
}