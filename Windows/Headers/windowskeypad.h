#ifndef WINDOWSKEYPAD_H
#define WINDOWSKEYPAD_H

#include <windows.h>
#include <windowsjoystick.h>
#include <windowskeyboard.h>
#include <program.h>
#include <process.h>

class WindowsKeypad : public Program {
private:
	static BOOL signalHandler(DWORD signalNum);

protected:
	void setupSignalHandler();

public:
	WindowsKeypad(char* fileLocation, MessageLogger* pLogger);
	virtual ~WindowsKeypad();
	virtual void run();
	virtual WindowsJoystick* getJoystick();
	virtual WindowsKeyboard* getKeyboard() { return dynamic_cast<WindowsKeyboard*>(p_keyboard); }
	void sendKeyPress(KeyboardButton button) { p_keyboard->sendKeyPress(&button); }

};

#endif