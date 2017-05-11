#include <windowsprogram.h>
#include <iostream>

WindowsProgram::WindowsProgram(char* fileLocation) :
	Program(fileLocation) {

	p_joystick = new WindowsJoystick();
	p_joystick->buttonPressed = [&](ControllerButton btn) { 
		_keyboard.sendKeyPress(getKeyMap()->getKeyboardButtonFor(btn));
	};
	p_joystick->buttonReleased = [&](ControllerButton btn) {
		_keyboard.sendKeyRelease(getKeyMap()->getKeyboardButtonFor(btn));
	};
}

void WindowsProgram::start() {
	_threadHandle = CreateThread(
		NULL,
		0,
		&WindowsProgram::getJoystickState,
		this,
		0,
		&_threadId
	);
}

WindowsProgram::~WindowsProgram() {
	Program::isRunning = false;
	WaitForSingleObject(_threadHandle, INFINITE);
	CloseHandle(_threadHandle);
}

WindowsJoystick* WindowsProgram::getJoystick() {
	return dynamic_cast<WindowsJoystick*>(p_joystick);
}

DWORD WINAPI WindowsProgram::getJoystickState(void* args) {
	Joystick* js = reinterpret_cast<WindowsProgram*>(args)->getJoystick();
	while (Program::isRunning) {
		js->fillState();
		Sleep(25);
	}
	return 0;
}