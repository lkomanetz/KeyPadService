#ifndef WINDOWSKEYBOARD_H
#define WINDOWSKEYBOARD_H

#include <keyboard.h>
#include <windows.h>

class WindowsKeyboard : public Keyboard {
public:
	WindowsKeyboard(MessageLogger* pLogger);
	void sendKeyPress(KeyboardButton* buttons);
	void sendKeyRelease(KeyboardButton* buttons);

};

#endif