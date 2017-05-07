#include <windowsprogram.h>
#include <iostream>

WindowsProgram::WindowsProgram() {
	p_joystick = new WindowsJoystick();
	p_joystick->buttonPressed = [&](ControllerButton btn) { 
		KeyboardButton* button = getKeyMap()->getKeyboardButtonFor(btn);
		std::cout << "Button " << *button << " pressed!" << std::endl;
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
	}
	return 0;
}