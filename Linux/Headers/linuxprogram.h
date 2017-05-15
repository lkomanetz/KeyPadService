#ifndef LINUXPROGRAM_H
#define LINUXPROGRAM_H

#include <linuxjoystick.h>
#include <linuxkeyboard.h>
#include <../../Headers/keypad.h>

class LinuxProgram : public Program {
private:
	int _fd;
	Display* p_display;
	Window _rootWindow;
	Window _focusedWindow;

	static void* getJoystickState(void*);

public:
	LinuxProgram(char* fileLocation);
	virtual ~LinuxProgram();
	virtual LinuxJoystick* getJoystick() const;
	virtual void sendKeyEvent(KeyboardButton button, short keyEvent);
	virtual void sendKeyPress(KeyboardButton btn) {}
	void getCurrentFocusedWindow();
};

#endif