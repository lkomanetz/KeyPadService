#ifndef LINUXPROGRAM_H
#define LINUXPROGRAM_H

#include <linuxjoystick.h>
#include <linuxkeyboard.h>
#include <../../Headers/keypad.h>

class LinuxProgram : public Program {
private:

	static void* getJoystickState(void*);

public:
	LinuxProgram(char* fileLocation);
	virtual ~LinuxProgram();
	virtual LinuxJoystick* getJoystick() const;
	virtual void sendKeyPress(KeyboardButton btn) {}
	void getCurrentFocusedWindow();
};

#endif