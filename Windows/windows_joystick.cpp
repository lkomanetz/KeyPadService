#include <windowsjoystick.h>

WindowsJoystick::WindowsJoystick() {
	_controllerNumber = 0;
	ZeroMemory(&_state, sizeof(Joystick_State));
}

WindowsJoystick::~WindowsJoystick() { }

void WindowsJoystick::initialize() {

}

bool WindowsJoystick::isButtonPressed(ControllerButton button) {
	return true;
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
	}
}