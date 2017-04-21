#include <joystick.h>

Joystick::Joystick() { }

Joystick::~Joystick() {
	close(_joystickFd);
	delete p_event;
}

Joystick::initialize() {
	_joystickFd = 0;
	_active = false;
	p_event = new js_event();

	_joystickFd = open(JOY_DEV, O_RDONLY | O_NONBLOCK);
	ioctl(_joystickFd, JSIOCGAXES, &_axisCount);
	ioctl(_joystickFd, JSIOCGBUTTONS, &_buttonCount);
	ioctl(_joystickFd, JSIOCGNAME(256), &_name);
}