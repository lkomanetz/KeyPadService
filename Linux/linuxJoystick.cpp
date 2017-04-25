#include <linuxjoystick.h>
#include <iostream>

LinuxJoystick::LinuxJoystick() {
	p_event = new js_event;
	this->initialize();
}

LinuxJoystick::~LinuxJoystick() {
	if (p_event)
		delete p_event;

	close(_joystickFd);
}

void LinuxJoystick::initialize() {
	_joystickFd = 0;
	_active = false;

	_joystickFd = open(JOY_DEV, O_RDONLY | O_NONBLOCK);
	ioctl(_joystickFd, JSIOCGAXES, &_axisCount);
	ioctl(_joystickFd, JSIOCGBUTTONS, &_buttonCount);
	ioctl(_joystickFd, JSIOCGNAME(256), &_name);

	fcntl(_joystickFd, F_SETFL, O_NONBLOCK);
	_active = _joystickFd >= 0;
}

//TODO(Logan) -> Implement this method to get the current state of the controller.
void LinuxJoystick::fillState() {
	int bytesRead = read(_joystickFd, p_event, sizeof(js_event));

	if (bytesRead == -1)
		return;

	switch (p_event->type & ~JS_EVENT_INIT) {
		case JS_EVENT_AXIS:
			_currentAxisStates[static_cast<ControllerButton>(p_event->number)] = p_event->value;
			break;
		case JS_EVENT_BUTTON:
			_currentButtonStates[p_event->number] = p_event->value;
			if (_buttonPressed != NULL) {
				ButtonPressedEventArgs args;
				args.button = p_event->number;
				args.isPressed = p_event->value == 1;
				_buttonPressed(args);
			}
			break;
	}
}