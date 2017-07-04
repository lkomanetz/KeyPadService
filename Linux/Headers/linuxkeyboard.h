#ifndef LINUXKEYBOARD_H
#define LINUXKEYBOARD_H

#include <unistd.h>
#include <fcntl.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include "keyboard.h"

namespace KeyboardEvents {
	const int KEY_PRESS = 1;
	const int KEY_RELEASE = 0;
}

class LinuxKeyboard : public Keyboard {
private:
	int _fd;

	int writeToInputBuffer(KeyboardButton* button, int kbEvent);

public:
	LinuxKeyboard(MessageLogger* pLogger);
	virtual ~LinuxKeyboard();
	void sendKeyPress(KeyboardButton* buttons);
	void sendKeyRelease(KeyboardButton* buttons);
};

#endif