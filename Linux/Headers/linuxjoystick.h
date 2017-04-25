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
#define MAX_AXIS_VALUE 32768

using namespace std;

struct ButtonPressedEventArgs {
	ControllerButton button;
	bool isPressed;
};

class LinuxJoystick : public Joystick {
private:
	unordered_map<ControllerButton, short> _currentButtonStates;
	unordered_map<short, short> _currentAxisStates;
	js_event* p_event;
	int _axisCount;
	int _buttonCount;
	int _joystickFd;
	bool _active;
	char _name[256];
	void (*_buttonPressed)(ButtonPressedEventArgs);

public:
	LinuxJoystick();
	virtual ~LinuxJoystick();
	virtual void initialize();
	virtual void fillState();
	virtual bool buttonPressed(ControllerButton button) { return _currentButtonStates[button] == 1; }
	char* getName() { return _name; }
	int getButtonCount() { return _buttonCount; }
	int getAxisCount() { return _axisCount; }
	short getAxisValue(const short axis) { return _currentAxisStates[axis]; }
	bool isActive() { return _active; }
	void setOnButtonPressedEvent(void (*buttonPressed)(ButtonPressedEventArgs)) { _buttonPressed = buttonPressed; }
};

#endif