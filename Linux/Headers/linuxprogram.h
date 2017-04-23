#ifndef LINUXPROGRAM_H
#define LINUXPROGRAM_H

#include <linuxjoystick.h>
#include <../../Headers/keypad.h>

class LinuxProgram : public Program {
private:

public:
	LinuxProgram();
	virtual LinuxJoystick* getJoystick();
};

#endif