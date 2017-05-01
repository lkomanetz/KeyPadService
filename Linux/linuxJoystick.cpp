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

		//TODO(Logan) -> Look at possibly refactoring this into a separate method.
		switch (p_event->type & ~JS_EVENT_INIT) {
			case JS_EVENT_AXIS:
				if ((evtNum == HORIZONTAL_AXIS || evtNum == VERTICAL_AXIS) ||
					p_event->value == 0) {
					
					_state.axisStates[ControllerButtons::DPAD_DOWN] = 0;
					_state.axisStates[ControllerButtons::DPAD_UP] = 0;
					_state.axisStates[ControllerButtons::DPAD_RIGHT] = 0;
					_state.axisStates[ControllerButtons::DPAD_LEFT] = 0;
				}

				if ((evtNum == HORIZONTAL_AXIS || evtNum == VERTICAL_AXIS) &&
					p_event->value != 0) {
					
					if (evtNum == HORIZONTAL_AXIS && p_event->value < 0) {
						_state.axisStates[ControllerButtons::DPAD_LEFT] = p_event->value;
					}
					else if (evtNum == HORIZONTAL_AXIS && p_event->value > 0) {
						_state.axisStates[ControllerButtons::DPAD_RIGHT] = p_event->value;
					}

					if (evtNum == VERTICAL_AXIS && p_event->value < 0) {
						_state.axisStates[ControllerButtons::DPAD_UP] = p_event->value;
					}
					else if (evtNum == VERTICAL_AXIS && p_event->value > 0) {
						_state.axisStates[ControllerButtons::DPAD_DOWN] = p_event->value;
					}
				}
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

	return _state.axisStates[button] != 0;
}

/*
 * Linux's Joystick.h treats the dpad buttons as if they were a joystick axis.  So I decided
 * that the directional pad buttons would be considered "axis buttons".
 */
bool LinuxJoystick::isAxisButton(ControllerButton button) {
	return (button == ControllerButtons::DPAD_DOWN ||
		button == ControllerButtons::DPAD_RIGHT ||
		button == ControllerButtons::DPAD_LEFT ||
		button == ControllerButtons::DPAD_UP);
}