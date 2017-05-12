#ifndef WINDOWSPROGRAM_H
#define WINDOWSPROGRAM_H

#include <windows.h>
#include <windowsjoystick.h>
#include <windowskeyboard.h>
#include <keypad.h>
#include <process.h>

class WindowsProgram : public Program {
public:
	WindowsProgram(char* fileLocation);
	virtual ~WindowsProgram();
	virtual WindowsJoystick* getJoystick();
	virtual WindowsKeyboard* getKeyboard() { return dynamic_cast<WindowsKeyboard*>(p_keyboard); }
	void sendKeyPress(KeyboardButton button) { p_keyboard->sendKeyPress(&button); }

};

#endif