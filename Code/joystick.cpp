#include <joystick.h>

Joystick::Joystick(MessageLogger* pLogger) {
	p_logger = pLogger;
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