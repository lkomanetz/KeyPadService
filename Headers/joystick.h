#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <keymapping.h>
#include <functional>

#define MIN_AXIS_VALUE -32768
#define MAX_AXIS_VALUE 32768

struct Joystick_State {
	unordered_map<ControllerButton, short> buttonStates;
	unordered_map<short, short> axisStates;
};

class Joystick {
protected:
	int _controllerNumber;
	Joystick_State _state;
	bool _active;

public:
	virtual void fillState() = 0;
	virtual void initialize() = 0;
	virtual bool isButtonPressed(ControllerButton button) = 0;
	virtual Joystick_State getCurrentState() { return _state; }
	bool isActive() { return _active; }
};

#endif
