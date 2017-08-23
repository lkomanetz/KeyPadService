#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <keymapping.h>
#include <functional>
#include <messagelogger.h>
#include <cmath>

#define MIN_AXIS_VALUE -32768
#define MAX_AXIS_VALUE 32768

struct Joystick_State {
	unordered_map<ControllerButton, bool> buttonStates;
	unordered_map<short, short> axisStates;
	bool isConnected;
};

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
	const ControllerButton DPAD_RIGHT = 11;
	const ControllerButton DPAD_LEFT = 12;
	const ControllerButton DPAD_UP = 13;
	const ControllerButton DPAD_DOWN = 14;
	const ControllerButton LEFT_STICK_LEFT = 15;
	const ControllerButton LEFT_STICK_UP = 16;
	const ControllerButton LEFT_STICK_RIGHT = 17;
	const ControllerButton LEFT_STICK_DOWN = 18;
}

class Joystick {
protected:
	int _controllerNumber;
	Joystick_State _state;
	bool _active;
	MessageLogger* p_logger;

public:
	Joystick(MessageLogger* pLogger);
	virtual ~Joystick();
	std::function<void(ControllerButton)> buttonPressed;
	std::function<void(ControllerButton)> buttonReleased;
	virtual void fillState() = 0;
	virtual void connect() = 0;
	virtual bool isButtonPressed(ControllerButton button) = 0;
	void setButtonState(ControllerButton btn, bool value, Joystick_State previousState);
	virtual Joystick_State getCurrentState() { return _state; }
	bool isActive() { return _active; }
};

#endif
