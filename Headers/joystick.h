#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <keymapping.h>

class Joystick {
private:
	bool _active;

public:
	virtual bool buttonPressed(const ControllerButton button) = 0;	
	virtual void getState() = 0;
	virtual void initialize() = 0;
	bool isActive() { return _active; }

};

#endif