#include <linuxprogram.h>

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
	}
}