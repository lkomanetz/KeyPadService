#include <linuxprogram.h>

LinuxProgram::LinuxProgram() {
	_joystick = new LinuxJoystick();
	_joystick->initialize();
}

LinuxJoystick* LinuxProgram::getJoystick() const {
	return dynamic_cast<LinuxJoystick*>(_joystick);
}
