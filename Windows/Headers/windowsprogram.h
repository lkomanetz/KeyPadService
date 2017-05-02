#ifndef WINDOWSPROGRAM_H
#define WINDOWSPROGRAM_H

#include <windows.h>
#include <windowsjoystick.h>
#include <keypad.h>
#include <process.h>

class WindowsProgram : public Program {
private:
	DWORD _threadId;
	HANDLE _threadHandle;

protected:
	static DWORD WINAPI getJoystickState(void* args);

public:
	WindowsProgram();
	virtual ~WindowsProgram();
	virtual WindowsJoystick* getJoystick();

};

#endif