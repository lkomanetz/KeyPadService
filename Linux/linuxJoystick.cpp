#include <linuxjoystick.h>

LinuxJoystick::LinuxJoystick() {
	this->initialize();
}

LinuxJoystick::~LinuxJoystick() {
	close(_joystickFd);
	delete p_event;
}

void LinuxJoystick::initialize() {
	_joystickFd = 0;
	_active = false;
	p_event = new js_event();

	_joystickFd = open(JOY_DEV, O_RDONLY | O_NONBLOCK);
	ioctl(_joystickFd, JSIOCGAXES, &_axisCount);
	ioctl(_joystickFd, JSIOCGBUTTONS, &_buttonCount);
	ioctl(_joystickFd, JSIOCGNAME(256), &_name);
	_active = _joystickFd >= 0;
}

//TODO(Logan) -> Implement this method for Linux joystick support.
bool LinuxJoystick::buttonPressed(const int button) {
	return true;
}

//TODO(Logan) -> Implement this method to get the current state of the controller.
void LinuxJoystick::getState() {

}
