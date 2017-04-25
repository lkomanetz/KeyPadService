#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <keymapping.h>

//TODO(Logan) -> Move value constants either in define statements or constants scoped to a namespace.
namespace ControllerButtons {
	const ControllerButton A_BUTTON = 0;
	const ControllerButton B_BUTTON = 1;
	const ControllerButton X_BUTTON = 2;
	const ControllerButton Y_BUTTON = 3;
	const ControllerButton LEFT_SHOULDER_BUTTON = 4;
	const ControllerButton RIGHT_SHOULDER_BUTTON = 5;
	const ControllerButton BACK_BUTTON = 6;
	const ControllerButton MENU_BUTTON = 7;
	const ControllerButton HOME_BUTTON = 8;
	const ControllerButton LEFT_STICK_BUTTON = 9;
	const ControllerButton RIGHT_STICK_BUTTON = 10;
	const ControllerButton DPAD_RIGHT = 6;
}

class Joystick {
private:
	bool _active;

public:
	virtual bool buttonPressed(const ControllerButton button) = 0;	
	virtual void fillState() = 0;
	virtual void initialize() = 0;
	bool isActive() { return _active; }

};

#endif
