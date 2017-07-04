#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <keymapping.h>
#include <messagelogger.h>

class Keyboard {
protected:
	MessageLogger* p_logger;

public:
	Keyboard(MessageLogger* pLogger) { p_logger = pLogger; }
	virtual void sendKeyPress(KeyboardButton* buttons) = 0;
	virtual void sendKeyRelease(KeyboardButton* buttons) = 0;
};

#endif