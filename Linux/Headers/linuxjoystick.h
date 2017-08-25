#ifndef LINUXJOYSTICK_H
#define LINUXJOYSTICK_H

#include <linux/joystick.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <joystick.h>
#include <keymapping.h>

#define LEFT_STICK_HORIZONTAL_AXIS 0
#define LEFT_STICK_VERTICAL_AXIS 1
#define RIGHT_STICK_HORIZONTAL_AXIS 3
#define RIGHT_STICK_VERTICAL_AXIS 4
#define DPAD_HORIZONTAL_AXIS 6
#define DPAD_VERTICAL_AXIS 7

typedef unsigned short ControllerAxis;

using namespace std;

class LinuxJoystick : public Joystick {
private:
	std::string _portName;
	int _axisCount;
	int _buttonCount;
	int _joystickFd;
	char _name[256];
	float _minimumAxisValue;
	float _axisDeadZone;
	
	void sendButtonPressedEvents();
	void setDpadButtonState(ControllerAxis axis, short rawValue, Joystick_State previousState);
	void setAxisState(ControllerAxis axis, short rawValue, Joystick_State previousState);

public:
	LinuxJoystick(MessageLogger* pLogger, std::string portName);
	virtual ~LinuxJoystick();
	virtual void fillState();
	virtual void connect();
	char* getName() { return _name; }
	int getButtonCount() { return _buttonCount; }
	int getAxisCount() { return _axisCount; }
	short getAxisValue(const short axis) { return _state.axisStates[axis]; }
};

#endif