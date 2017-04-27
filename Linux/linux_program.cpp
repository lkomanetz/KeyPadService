#include <linuxprogram.h>
#include <iostream>

LinuxProgram::LinuxProgram() {
	_exitThread = false;
	_joystick = new LinuxJoystick();
	_joystick->initialize();
	pthread_create(&_jsStateThread, NULL, &LinuxProgram::getJoystickState, this);
}

LinuxProgram::~LinuxProgram() {
	_exitThread = true;
	pthread_join(_jsStateThread, NULL);
}

LinuxJoystick* LinuxProgram::getJoystick() const {
	return dynamic_cast<LinuxJoystick*>(_joystick);
}

void* LinuxProgram::getJoystickState(void* obj) {
	bool exitThread = reinterpret_cast<LinuxProgram*>(obj)->_exitThread;
	Joystick* js = reinterpret_cast<LinuxProgram*>(obj)->getJoystick();

	std::cout << "I am starting to get Joystick state!" << std::endl;
	while (!exitThread) {
		js->fillState();
	}
	
	std::cout << "I am done!" << std::endl;
	pthread_exit(NULL);
}