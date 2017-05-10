#ifndef WINDOWSPROGRAM_H
#define WINDOWSPROGRAM_H

#include <windows.h>
#include <windowsjoystick.h>
#include <windowskeyboard.h>
#include <keypad.h>
#include <process.h>

class WindowsProgram : public Program {
private:
	DWORD _threadId;
	HANDLE _threadHandle;
	WindowsKeyboard _keyboard;

protected:
	static DWORD WINAPI getJoystickState(void* args);

public:
	WindowsProgram(char* fileLocation);
	virtual ~WindowsProgram();
	virtual WindowsJoystick* getJoystick();
	virtual WindowsKeyboard* getKeyboard() { return &_keyboard; }
	virtual void start();
	void sendKeyPress(KeyboardButton button) { _keyboard.sendKeyPress(&button); }

};

#endif