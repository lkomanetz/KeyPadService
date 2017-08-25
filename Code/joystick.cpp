#include <joystick.h>

Joystick::Joystick(MessageLogger* pLogger) {
	p_logger = pLogger;
	p_logger->log("Attempting to connect joystick.");
	_axisDeadZone = MAX_AXIS_VALUE * 0.25f;
	_minimumAxisValue = MAX_AXIS_VALUE * 0.75f;
}

Joystick::~Joystick() {
	p_logger->log("Joystick disconnected.");
}

void Joystick::setButtonState(
	ControllerButton btn,
	bool value,
	Joystick_State previousState
) {
	_state.buttonStates[btn] = value;

	if (value == true) {
		buttonPressed(btn);
	}
	else if (previousState.buttonStates[btn] == true && value == false) {
		buttonReleased(btn);
	}

}