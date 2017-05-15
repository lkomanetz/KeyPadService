#ifndef LINUXKEYBOARD_H
#define LINUXKEYBOARD_H

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
	int writeToInputBuffer(KeyboardButton* button);

public:
	void sendKeyPress(KeyboardButton* buttons);
	void sendKeyRelease(KeyboardButton* buttons);
};

#endif