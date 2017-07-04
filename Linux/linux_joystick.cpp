#include <linuxjoystick.h>

LinuxJoystick::LinuxJoystick(MessageLogger* pLogger) : 
	Joystick(pLogger) {

	p_event = new js_event;
	_joystickFd = -1;
}

LinuxJoystick::~LinuxJoystick() {
	if (p_event) {
		delete p_event;
		p_event = NULL;
	}

	close(_joystickFd);
	if (_active) {
		p_logger->log("Joystick disconnected");
	}
}

void LinuxJoystick::connect() {
	_joystickFd = open(JOY_DEV, O_RDONLY | O_NONBLOCK);
	fcntl(_joystickFd, F_SETFL, O_NONBLOCK);

	_active = _joystickFd >= 0;
	if (_active) {
		p_logger->log("Joystick connected");
	}
}

void LinuxJoystick::fillState() {
	Joystick_State previousState = _state;

	int bytesRead = read(_joystickFd, p_event, sizeof(js_event));
	if (bytesRead == -1) {
		sendButtonPressedEvents();
		return;
	}

	//TODO(Logan) -> Look at possibly refactoring this into a separate method.
	switch (p_event->type & ~JS_EVENT_INIT) {
		case JS_EVENT_AXIS: {
			ControllerAxis axis = static_cast<ControllerAxis>(p_event->number);
			if ((axis == VERTICAL_AXIS) && p_event->value == 0) {
				setButtonState(ControllerButtons::DPAD_DOWN, false, previousState);
				setButtonState(ControllerButtons::DPAD_UP, false, previousState);
			}
			else if ((axis == HORIZONTAL_AXIS) && p_event->value == 0) {
				setButtonState(ControllerButtons::DPAD_RIGHT, false, previousState);
				setButtonState(ControllerButtons::DPAD_LEFT, false, previousState);
			}

			if ((axis == HORIZONTAL_AXIS || axis == VERTICAL_AXIS) &&
				p_event->value != 0) {
				
				if (axis == HORIZONTAL_AXIS && p_event->value < 0) {
					setButtonState(ControllerButtons::DPAD_LEFT, true, previousState);
				}
				else if (axis == HORIZONTAL_AXIS && p_event->value > 0) {
					setButtonState(ControllerButtons::DPAD_RIGHT, true, previousState);
				}

				if (axis == VERTICAL_AXIS && p_event->value < 0) {
					setButtonState(ControllerButtons::DPAD_UP, true, previousState);
				}
				else if (axis == VERTICAL_AXIS && p_event->value > 0) {
					setButtonState(ControllerButtons::DPAD_DOWN, true, previousState);
				}
			}
			break;
		}
		case JS_EVENT_BUTTON: {
			ControllerButton btn = static_cast<ControllerButton>(p_event->number);
			setButtonState(btn, p_event-> value == 1, previousState);
			break;
		}
	}
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

	for (auto it : _state.axisStates) {
		if (it.second != 0) {
			buttonPressed(it.first);
		}
	}
}