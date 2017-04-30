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

void LinuxJoystick::fillState() {
	while (true) {
		int bytesRead = read(_joystickFd, p_event, sizeof(js_event));

		if (bytesRead == -1)
			return;
		
		ControllerButton evtNum = static_cast<ControllerButton>(p_event->number);
		switch (p_event->type & ~JS_EVENT_INIT) {
			case JS_EVENT_AXIS:
				_state.axisStates[evtNum] = p_event->value;
				break;
			case JS_EVENT_BUTTON:
				_state.buttonStates[evtNum] = p_event->value;
				break;
		}
	}
}

bool LinuxJoystick::isButtonPressed(ControllerButton button) {
	if (!this->isAxisButton(button))
		return _state.buttonStates[button] == 1;

	std::cout << "Button '" << button << "' Value: '" << _state.axisStates[button] << std::endl;
	/*
	short value = _state.axisStates[button];
	if ((button == ControllerButtons::DPAD_LEFT || button == ControllerButtons::DPAD_DOWN) &&
		value < 0)
		return true;
	else if ((button == ControllerButtons::DPAD_RIGHT || button == ControllerButtons::DPAD_UP) &&
		value > 0)
		return true;
	else
		return false;
	*/
	return false;
}

bool LinuxJoystick::isAxisButton(ControllerButton button) {
	return (button == ControllerButtons::DPAD_DOWN ||
		button == ControllerButtons::DPAD_RIGHT ||
		button == ControllerButtons::DPAD_LEFT ||
		button == ControllerButtons::DPAD_UP);
}