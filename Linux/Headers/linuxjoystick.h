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
/*
#define JS_EVENT_BUTTON 0x01 // Button is pressed/released
#define JS_EVENT_AXIS 0x02 // Joystick has moved
#define JS_EVENT_INIT 0x03 // Initial state of joystick
*/
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
	bool buttonPressed(ControllerButton button);
	void readEvent();
	void initialize();
	void getState();
	char* getName() { return _name; }
	int getButtonCount() { return _buttonCount; }
	int getAxisCount() { return _axisCount; }
	bool isActive() { return _active; }
};

/*
class JoystickEvent {
public:
	unsigned int eventTimestampMilliseconds;
	EventValue value;
	EventType type;
	ActionIndex index;

	bool isButton() { return (type & JS_EVENT_BUTTON) != 0; }
	bool isAxis() { return (type & JS_EVENT_AXIS) != 0; }
	bool isInitialState() { return (type & JS_EVENT_INIT) != 0; }
};
*/

#endif