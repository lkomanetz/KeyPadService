#ifndef LINUXPROGRAM_H
#define LINUXPROGRAM_H

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <pthread.h>
#include <linuxjoystick.h>
#include <../../Headers/keypad.h>

class LinuxProgram : public Program {
private:
	int _fd;
	Display* p_display;
	Window _rootWindow;
	Window _focusedWindow;

	pthread_t _jsStateThread;
	static void* getJoystickState(void*);

public:
	LinuxProgram(char* fileLocation);
	virtual ~LinuxProgram();
	virtual LinuxJoystick* getJoystick() const;
	virtual void sendKeyEvent(KeyboardButton button, short keyEvent);
	virtual void sendKeyPress(KeyboardButton btn) {}
	virtual void start();
	void getCurrentFocusedWindow();
};

#endif