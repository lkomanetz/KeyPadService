#include <linuxjoystick.h>

LinuxJoystick::LinuxJoystick() {
	p_event = new js_event;
	_joystickFd = 0;
	_active = false;

	_joystickFd = open(JOY_DEV, O_RDONLY | O_NONBLOCK);
	ioctl(_joystickFd, JSIOCGAXES, &_axisCount);
	ioctl(_joystickFd, JSIOCGBUTTONS, &_buttonCount);
	ioctl(_joystickFd, JSIOCGNAME(256), &_name);

	fcntl(_joystickFd, F_SETFL, O_NONBLOCK);
	_active = _joystickFd >= 0;
}

LinuxJoystick::~LinuxJoystick() {
	if (p_event)
		delete p_event;

	close(_joystickFd);
}

void LinuxJoystick::fillState() {
	int bytesRead = read(_joystickFd, p_event, sizeof(js_event));
	if (bytesRead == -1) {
		sendButtonPressedEvents();
		return;
	}
	
	ControllerButton evtNum = static_cast<ControllerButton>(p_event->number);
	Joystick_State previousState = _state;

	//TODO(Logan) -> Look at possibly refactoring this into a separate method.
	switch (p_event->type & ~JS_EVENT_INIT) {
		case JS_EVENT_AXIS:
			if ((evtNum == HORIZONTAL_AXIS || evtNum == VERTICAL_AXIS) &&
				p_event->value == 0) {
				
				_state.axisStates[ControllerButtons::DPAD_DOWN] = 0;
				_state.axisStates[ControllerButtons::DPAD_UP] = 0;
				_state.axisStates[ControllerButtons::DPAD_RIGHT] = 0;
				_state.axisStates[ControllerButtons::DPAD_LEFT] = 0;
			}

			if ((evtNum == HORIZONTAL_AXIS || evtNum == VERTICAL_AXIS) &&
				p_event->value != 0) {
				
				if (evtNum == HORIZONTAL_AXIS && p_event->value < 0) {
					_state.axisStates[ControllerButtons::DPAD_LEFT] = true;
				}
				else if (evtNum == HORIZONTAL_AXIS && p_event->value > 0) {
					_state.axisStates[ControllerButtons::DPAD_RIGHT] = true;
				}

				if (evtNum == VERTICAL_AXIS && p_event->value < 0) {
					_state.axisStates[ControllerButtons::DPAD_UP] = true;
				}
				else if (evtNum == VERTICAL_AXIS && p_event->value > 0) {
					_state.axisStates[ControllerButtons::DPAD_DOWN] = true;
				}
			}
			break;
		case JS_EVENT_BUTTON:
			bool wasPressed = isButtonPressed(evtNum);
			_state.buttonStates[evtNum] = p_event->value == 1;
			if (wasPressed && _state.buttonStates[evtNum] == false) {
				buttonReleased(evtNum);
			}
			break;
	}

	sendButtonPressedEvents();
}

bool LinuxJoystick::isButtonPressed(ControllerButton button) {
	if (!this->isAxisButton(button))
		return _state.buttonStates[button];

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

void LinuxJoystick::sendButtonPressedEvents() {
	for (auto it : _state.buttonStates) {
		if (it.second == true) {
			buttonPressed(it.first);
		}
	}
}