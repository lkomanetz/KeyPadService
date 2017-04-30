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
	const ControllerButton DPAD_LEFT = 6;
	const ControllerButton DPAD_UP = 7;
	const ControllerButton DPAD_DOWN = 7;
}

struct Joystick_State {
	unordered_map<ControllerButton, short> buttonStates;
	unordered_map<short, short> axisStates;
};

using namespace std;

class LinuxJoystick : public Joystick {
private:
	Joystick_State _state;
	js_event* p_event;
	int _axisCount;
	int _buttonCount;
	int _joystickFd;
	bool _active;
	char _name[256];
	
	bool isAxisButton(ControllerButton button);

public:
	LinuxJoystick();
	virtual ~LinuxJoystick();
	virtual void initialize();
	virtual void fillState();
	virtual Joystick_State getCurrentState() { return _state; }
	virtual bool isButtonPressed(ControllerButton button);
	char* getName() { return _name; }
	int getButtonCount() { return _buttonCount; }
	int getAxisCount() { return _axisCount; }
	short getAxisValue(const short axis) { return _state.axisStates[axis]; }
	bool isActive() { return _active; }
};

#endif