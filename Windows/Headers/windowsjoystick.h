#ifndef WINDOWS_JOYSTICK
#define WINDOWS_JOYSTICK

#include <keymapping.h>
#include <joystick.h>
#include <windows.h>
#include <XInput.h>

class WindowsJoystick : public Joystick {
public:
	WindowsJoystick();
	~WindowsJoystick();
	virtual void fillState();
	virtual bool isButtonPressed(ControllerButton button);

};

#endif