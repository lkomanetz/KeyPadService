#ifndef LINUXPROGRAM_H
#define LINUXPROGRAM_H

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <linux/input.h>
#include <pthread.h>
#include <linuxjoystick.h>
#include <../../Headers/keypad.h>

class LinuxProgram : public Program {
private:
	Display* p_display;
	Window _rootWindow;
	Window _focusedWindow;

	pthread_t _jsStateThread;
	static void* getJoystickState(void*);

public:
	LinuxProgram();
	virtual ~LinuxProgram();
	virtual LinuxJoystick* getJoystick() const;
	virtual void sendKeyPress(KeyboardButton button);
	void getCurrentFocusedWindow();
};

#endif
