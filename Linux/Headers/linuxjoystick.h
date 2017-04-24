#ifndef LINUXJOYSTICK_H
#define LINUXJOYSTICK_H

#include <linux/joystick.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <joystick.h>
#include <keymapping.h>

typedef unsigned char EventType;
typedef unsigned char ActionIndex;
typedef short EventValue;

#define JOY_DEV "/dev/input/js0"
#define MIN_AXIS_VALUE -32768
#define MAX_AXI_VALUE 32768

using namespace std;

class LinuxJoystick : public Joystick {
private:
	unordered_map<ControllerButton, short> _currentButtonStates;
	js_event* p_event;
	int _axisCount;
	int _buttonCount;
	int _joystickFd;
	bool _active;
	char _name[256];

public:
	LinuxJoystick();
	virtual ~LinuxJoystick();
	virtual void initialize();
	virtual void fillState();
	virtual bool buttonPressed(ControllerButton button);
	char* getName() { return _name; }
	int getButtonCount() { return _buttonCount; }
	int getAxisCount() { return _axisCount; }
	bool isActive() { return _active; }
};

#endif