//TODO(Logan) -> Get rid of unnecessary cout statements.
#include <windowsprogram.h>
#include <iostream>

WindowsProgram::WindowsProgram() {
	p_joystick = new WindowsJoystick();
	p_joystick->initialize();

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
	std::cout << "Destructing Windows Program" << std::endl;
	Program::isRunning = false;
	WaitForSingleObject(_threadHandle, INFINITE);
	CloseHandle(_threadHandle);
}

WindowsJoystick* WindowsProgram::getJoystick() {
	return dynamic_cast<WindowsJoystick*>(p_joystick);
}

DWORD WINAPI WindowsProgram::getJoystickState(void* args) {
	while (Program::isRunning) {

	}

	std::cout << "Getting joystick stick is done" << std::endl;
	return 0;
}