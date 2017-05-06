#include <joystick.h>

void Joystick::determineIfPressedOrReleased(
	ControllerButton button,
	Joystick_State currentState,
	Joystick_State previousState
) {
	if (currentState.buttonStates[button] == true) {
		buttonPressed(button);
	}
	else if (previousState.buttonStates[button] == true &&
		currentState.buttonStates[button] == false) {

		buttonReleased(button);
	}
}