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
	const ControllerButton DPAD_RIGHT = 6; // DPAD_LEFT and DPAD_RIGHT axis is 6
	const ControllerButton DPAD_LEFT = 7;
	const ControllerButton DPAD_UP = 8; // DPAD_UP and DPAD_DOWN axis is 7
	const ControllerButton DPAD_DOWN = 9;
}

using namespace std;

class LinuxJoystick : public Joystick {
private:
	js_event* p_event;
	int _axisCount;
	int _buttonCount;
	int _joystickFd;
	char _name[256];
	
	bool isAxisButton(ControllerButton button);

public:
	LinuxJoystick();
	virtual ~LinuxJoystick();
	virtual void initialize();
	virtual void fillState();
	virtual bool isButtonPressed(ControllerButton button);
	char* getName() { return _name; }
	int getButtonCount() { return _buttonCount; }
	int getAxisCount() { return _axisCount; }
	short getAxisValue(const short axis) { return _state.axisStates[axis]; }
};

#endif