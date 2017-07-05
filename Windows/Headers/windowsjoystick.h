#ifndef WINDOWS_JOYSTICK
#define WINDOWS_JOYSTICK

#include <keymapping.h>
#include <joystick.h>
#include <windows.h>
#include <XInput.h>

class WindowsJoystick : public Joystick {
public:
	WindowsJoystick(MessageLogger* pLogger);
	~WindowsJoystick();
	virtual void fillState();
	virtual void connect();
	virtual bool isButtonPressed(ControllerButton button);

};

#endif