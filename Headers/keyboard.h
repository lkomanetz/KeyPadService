#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <keymapping.h>

class Keyboard {
public:
	virtual void sendKeyPress(KeyboardButton* buttons) = 0;
	virtual void sendKeyRelease(KeyboardButton* buttons) = 0;
};

#endif