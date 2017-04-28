#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <keymapping.h>
#include <functional>

#define MIN_AXIS_VALUE -32768
#define MAX_AXIS_VALUE 32768

struct Joystick_State;

class Joystick {
private:
	bool _active;

public:
	virtual void fillState() = 0;
	virtual void initialize() = 0;
	virtual Joystick_State getCurrentState() = 0;
	bool isActive() { return _active; }
};

#endif
