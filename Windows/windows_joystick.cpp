#include <windowsjoystick.h>

WindowsJoystick::WindowsJoystick() {
	_controllerNumber = 0;
}

WindowsJoystick::~WindowsJoystick() { }

bool WindowsJoystick::isButtonPressed(ControllerButton button) {
	return _state.buttonStates[button];
}

void WindowsJoystick::fillState() {
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	DWORD result = XInputGetState(_controllerNumber, &state);

	if (result == ERROR_SUCCESS) {
		_active = true;
	}
	else {
		_active = false;
		return;
	}

	XINPUT_GAMEPAD gp = state.Gamepad;
	Joystick_State previousState = _state;

	_state.buttonStates[ControllerButtons::A_BUTTON] = (gp.wButtons & XINPUT_GAMEPAD_A) != 0;
	_state.buttonStates[ControllerButtons::B_BUTTON] = (gp.wButtons & XINPUT_GAMEPAD_B) != 0;
	_state.buttonStates[ControllerButtons::X_BUTTON] = (gp.wButtons & XINPUT_GAMEPAD_X) != 0;
	_state.buttonStates[ControllerButtons::Y_BUTTON] = (gp.wButtons & XINPUT_GAMEPAD_Y) != 0;
	_state.buttonStates[ControllerButtons::LEFT_SHOULDER_BUTTON] = (gp.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0;
	_state.buttonStates[ControllerButtons::RIGHT_SHOULDER_BUTTON] = (gp.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0;
	_state.buttonStates[ControllerButtons::LEFT_STICK_BUTTON] = (gp.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0;
	_state.buttonStates[ControllerButtons::RIGHT_STICK_BUTTON] = (gp.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0;
	_state.buttonStates[ControllerButtons::BACK_BUTTON] = (gp.wButtons & XINPUT_GAMEPAD_BACK) != 0;
	_state.buttonStates[ControllerButtons::MENU_BUTTON] = (gp.wButtons & XINPUT_GAMEPAD_START) != 0;
	_state.buttonStates[ControllerButtons::DPAD_UP] = (gp.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0;
	_state.buttonStates[ControllerButtons::DPAD_DOWN] = (gp.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0;
	_state.buttonStates[ControllerButtons::DPAD_LEFT] = (gp.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0;
	_state.buttonStates[ControllerButtons::DPAD_RIGHT] = (gp.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0;

	determineIfPressedOrReleased(ControllerButtons::A_BUTTON, _state, previousState);
	determineIfPressedOrReleased(ControllerButtons::B_BUTTON, _state, previousState);
	determineIfPressedOrReleased(ControllerButtons::X_BUTTON, _state, previousState);
	determineIfPressedOrReleased(ControllerButtons::Y_BUTTON, _state, previousState);
	determineIfPressedOrReleased(ControllerButtons::LEFT_SHOULDER_BUTTON, _state, previousState);
	determineIfPressedOrReleased(ControllerButtons::RIGHT_SHOULDER_BUTTON, _state, previousState);
	determineIfPressedOrReleased(ControllerButtons::LEFT_STICK_BUTTON, _state, previousState);
	determineIfPressedOrReleased(ControllerButtons::RIGHT_STICK_BUTTON, _state, previousState);
	determineIfPressedOrReleased(ControllerButtons::BACK_BUTTON, _state, previousState);
	determineIfPressedOrReleased(ControllerButtons::MENU_BUTTON, _state, previousState);
	determineIfPressedOrReleased(ControllerButtons::DPAD_UP, _state, previousState);
	determineIfPressedOrReleased(ControllerButtons::DPAD_DOWN, _state, previousState);
	determineIfPressedOrReleased(ControllerButtons::DPAD_RIGHT, _state, previousState);
	determineIfPressedOrReleased(ControllerButtons::DPAD_LEFT, _state, previousState);
}