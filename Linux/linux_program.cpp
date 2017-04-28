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

		// TODO(Logan) -> I still have to figure out how to handle axis values
		for (auto it : state.axisStates) {
			std::cout << "Axis '" << it.first << "' Value " << it.second << std::endl;
			/*
			if (it.second == 32768 || it.second == -32768) {
				std::cout << "Axis '" << it.first << "' is pressed!" << std::endl;
			}
			*/
		}
	}
}