#ifndef LINUXPROGRAM_H
#define LINUXPROGRAM_H

#include <linuxjoystick.h>
#include <../../Headers/keypad.h>

//TODO(Logan) -> I want to add some events that make it so on button pressed/released a function pointer
// gets called, and there is a handler that will map it to the correct keyboard button.  Right now in my
// head the program should just let the Joystick classes poll the controller's state, and then the Joystick
// classes' events will be observed by the program to convert controller button to keyboard button and send
// the keyboard input somehow.

class LinuxProgram : public Program {
private:

public:
	//TODO(Logan) -> Add a way to pass in the key mapping that gets used internally.
	//TODO(Logan) -> Add some event handlers that listen to the joystick's events.
	LinuxProgram();
	virtual LinuxJoystick* getJoystick() const;
};

#endif
