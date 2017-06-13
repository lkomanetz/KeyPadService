#ifndef LINUXKEYPAD_H
#define LINUXKEYPAD_H

#include <linuxjoystick.h>
#include <linuxkeyboard.h>
#include <../../Headers/program.h>

class LinuxKeypad : public Program {
private:

	static void* getJoystickState(void*);

public:
	LinuxKeypad();
	LinuxKeypad(char* fileLocation, MessageLogger* pLogger);
	virtual ~LinuxKeypad();
	virtual LinuxJoystick* getJoystick() const;
	virtual void sendKeyPress(KeyboardButton btn) {}
	virtual void run();
	void getCurrentFocusedWindow();
};

#endif