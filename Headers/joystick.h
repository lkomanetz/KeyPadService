#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <keymapping.h>
#include <functional>

#define MIN_AXIS_VALUE -32768
#define MAX_AXIS_VALUE 32768

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

struct ButtonPressedEventArgs {
	ControllerButton button;
	bool isPressed;
};

class Joystick {
private:
	bool _active;

public:
	virtual void fillState() = 0;
	virtual void initialize() = 0;
	bool isActive() { return _active; }
};

#endif
