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

	setButtonState(ControllerButtons::A_BUTTON, (gp.wButtons & XINPUT_GAMEPAD_A) != 0, previousState);
	setButtonState(ControllerButtons::B_BUTTON, (gp.wButtons & XINPUT_GAMEPAD_B) != 0, previousState);
	setButtonState(ControllerButtons::X_BUTTON, (gp.wButtons & XINPUT_GAMEPAD_X) != 0, previousState);
	setButtonState(ControllerButtons::Y_BUTTON, (gp.wButtons & XINPUT_GAMEPAD_Y) != 0, previousState);
	setButtonState(ControllerButtons::LEFT_SHOULDER_BUTTON, (gp.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0, previousState);
	setButtonState(ControllerButtons::RIGHT_SHOULDER_BUTTON, (gp.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0, previousState);
	setButtonState(ControllerButtons::LEFT_STICK_BUTTON, (gp.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0, previousState);
	setButtonState(ControllerButtons::RIGHT_STICK_BUTTON, (gp.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0, previousState);
	setButtonState(ControllerButtons::BACK_BUTTON, (gp.wButtons & XINPUT_GAMEPAD_BACK) != 0, previousState);
	setButtonState(ControllerButtons::MENU_BUTTON, (gp.wButtons & XINPUT_GAMEPAD_START) != 0, previousState);
	setButtonState(ControllerButtons::DPAD_UP, (gp.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0, previousState);
	setButtonState(ControllerButtons::DPAD_DOWN, (gp.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0, previousState);
	setButtonState(ControllerButtons::DPAD_LEFT, (gp.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0, previousState);
	setButtonState(ControllerButtons::DPAD_RIGHT, (gp.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0, previousState);
}