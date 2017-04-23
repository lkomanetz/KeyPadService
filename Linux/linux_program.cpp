#include <linuxprogram.h>

LinuxProgram::LinuxProgram() {
	_joystick = new LinuxJoystick();
	_joystick->initialize();
}

LinuxJoystick* LinuxProgram::getJoystick() {
	return dynamic_cast<LinuxJoystick*>(_joystick);
}