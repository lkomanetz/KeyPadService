#ifndef LINUXJOYSTICK_H
#define LINUXJOYSTICK_H

#include <linux/joystick.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <joystick.h>
#include <keymapping.h>

#define JOY_DEV "/dev/input/js0"
#define HORIZONTAL_AXIS 6
#define VERTICAL_AXIS 7

typedef unsigned short ControllerAxis;

using namespace std;

class LinuxJoystick : public Joystick {
private:
	js_event* p_event;
	int _axisCount;
	int _buttonCount;
	int _joystickFd;
	char _name[256];
	
	bool isAxisButton(ControllerButton button);
	void sendButtonPressedEvents();

public:
	LinuxJoystick();
	virtual ~LinuxJoystick();
	virtual void fillState();
	virtual bool isButtonPressed(ControllerButton button);
	char* getName() { return _name; }
	int getButtonCount() { return _buttonCount; }
	int getAxisCount() { return _axisCount; }
	short getAxisValue(const short axis) { return _state.axisStates[axis]; }
};

#endif