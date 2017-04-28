#include <../Headers/keypad.h>

bool Program::isRunning = false;

Program::Program() {
	Program::isRunning = true;
	p_joystick = NULL;
}

Program::~Program() {
	if (p_joystick) {
		delete p_joystick;
	}
}