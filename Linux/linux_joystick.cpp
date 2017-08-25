#include <linuxjoystick.h>

LinuxJoystick::LinuxJoystick(MessageLogger* pLogger, std::string portName) : 
	Joystick(pLogger) {

	_joystickFd = -1;
	_portName = portName;
}

LinuxJoystick::~LinuxJoystick() {
	close(_joystickFd);
}

void LinuxJoystick::connect() {
	_joystickFd = open(_portName.c_str(), O_RDONLY | O_NONBLOCK);
	fcntl(_joystickFd, F_SETFL, O_NONBLOCK);

	_active = _joystickFd >= 0;
	if (_active) {
		p_logger->log("Joystick connected");
	}
}

void LinuxJoystick::fillState() {
	js_event evt = {};
	Joystick_State previousState = _state;

	int bytesRead = read(_joystickFd, &evt, sizeof(js_event));
	if (bytesRead == -1) {
		sendButtonPressedEvents();
		return;
	}

	switch (evt.type & ~JS_EVENT_INIT) {
		case JS_EVENT_AXIS: {
			ControllerAxis axis = static_cast<ControllerAxis>(evt.number);
			setDpadButtonState(axis, evt.value, previousState);
			setAxisState(axis, evt.value, previousState);
			break;
		}
		case JS_EVENT_BUTTON: {
			ControllerButton btn = static_cast<ControllerButton>(evt.number);
			setButtonState(btn, evt.value == 1, previousState);
			break;
		}
	}
}

/*
 * With reading from the joystick port, nothing is written into that event file unless
 * a value has changed.  For example if a button is still pressed the next time it is
 * checked nothing is read from the file (there is nothing to read).  So to make sure
 * button pressed events are still going through I send an event for every button still
 * pressed down.
 */
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

void LinuxJoystick::setDpadButtonState(ControllerAxis axis, short rawValue, Joystick_State previousState) {
	if ((axis == DPAD_VERTICAL_AXIS) && rawValue == 0) {
		setButtonState(ControllerButtons::DPAD_DOWN, false, previousState);
		setButtonState(ControllerButtons::DPAD_UP, false, previousState);
	}
	else if ((axis == DPAD_HORIZONTAL_AXIS) && rawValue == 0) {
		setButtonState(ControllerButtons::DPAD_RIGHT, false, previousState);
		setButtonState(ControllerButtons::DPAD_LEFT, false, previousState);
	}

	if ((axis == DPAD_HORIZONTAL_AXIS || axis == DPAD_VERTICAL_AXIS) &&
		rawValue != 0) {
		
		if (axis == DPAD_HORIZONTAL_AXIS && rawValue < 0) {
			setButtonState(ControllerButtons::DPAD_LEFT, true, previousState);
		}
		else if (axis == DPAD_HORIZONTAL_AXIS && rawValue > 0) {
			setButtonState(ControllerButtons::DPAD_RIGHT, true, previousState);
		}

		if (axis == DPAD_VERTICAL_AXIS && rawValue < 0) {
			setButtonState(ControllerButtons::DPAD_UP, true, previousState);
		}
		else if (axis == DPAD_VERTICAL_AXIS && rawValue > 0) {
			setButtonState(ControllerButtons::DPAD_DOWN, true, previousState);
		}
	}
}

void LinuxJoystick::setAxisState(ControllerAxis axis, short rawValue, Joystick_State previousState) {
	ControllerButton btn = -1;

	switch (axis) {
		case LEFT_STICK_HORIZONTAL_AXIS:
			btn = (rawValue >= 0) ? ControllerButtons::LEFT_STICK_RIGHT : ControllerButtons::LEFT_STICK_LEFT;
			break;
		case LEFT_STICK_VERTICAL_AXIS:
			btn = (rawValue >= 0) ? ControllerButtons::LEFT_STICK_DOWN : ControllerButtons::LEFT_STICK_UP;
			break;
		case RIGHT_STICK_HORIZONTAL_AXIS:
		case RIGHT_STICK_VERTICAL_AXIS:
			//TODO(Logan) -> Figure out how to handle mapping both analog sticks.
			break;
	}

	bool axisPressed = false;
	switch (btn) {
		case ControllerButtons::LEFT_STICK_LEFT:
		case ControllerButtons::LEFT_STICK_UP:
			axisPressed = (rawValue < -_axisDeadZone && rawValue <= -_minimumAxisValue);
			break;
		case ControllerButtons::LEFT_STICK_RIGHT:
		case ControllerButtons::LEFT_STICK_DOWN:
			axisPressed = (rawValue > _axisDeadZone && rawValue >= _minimumAxisValue);
			break;
	}

	setButtonState(btn, axisPressed, previousState);
}