#include <../Headers/keypad.h>

Program::Program() {
	_joystick = NULL;
}

Program::~Program() {
	if (_joystick) {
		delete _joystick;
	}
}