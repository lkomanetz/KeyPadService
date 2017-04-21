#ifndef LINUXPROGRAM_H
#define LINUXPROGRAM_H

#include <linux/joystick.h>
#include <../../Headers/keypad.h>
#include <joystick.h>

class LinuxProgram : public Program {
private:
	Joystick _joystick;

public:
	void initializeController();
	Joystick getJoystick() { return _joystick; }
};

#endif