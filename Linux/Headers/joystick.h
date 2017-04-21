#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <linux/joystick.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define JOY_DEV "/dev/input/js0"

class Joystick {
private:
	int _axisCount;
	int _buttonCount;
	int _joystickFd;
	bool _active;
	js_event* p_event;
	char _name[256];

public:
	Joystick();
	~Joystick();
	bool buttonPressed(int button);
	void readEvent();
	void initialize();
	char* getName() { return _name; }
	int getButtonCount() { return _buttonCount; }
	int getAxisCount() { return _axisCount; }
	int getFd() { return _joystickFd; }
};

#endif