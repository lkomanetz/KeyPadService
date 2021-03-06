#include <windowskeyboard.h>

WindowsKeyboard::WindowsKeyboard(MessageLogger* pLogger) :
	Keyboard(pLogger) {}

void WindowsKeyboard::sendKeyPress(KeyboardButton* buttons) {
	KEYBDINPUT kb = {};
	INPUT input = {};

	kb.wVk = *buttons;
	kb.dwFlags = 0;
	input.type = INPUT_KEYBOARD;
	input.ki = kb;

	SendInput(1, &input, sizeof(input));
}

void WindowsKeyboard::sendKeyRelease(KeyboardButton* buttons) {
	KEYBDINPUT kb = {};
	INPUT input = {};

	kb.dwFlags = KEYEVENTF_KEYUP;
	kb.wVk = *buttons;
	input.type = INPUT_KEYBOARD;
	input.ki = kb;

	SendInput(1, &input, sizeof(input));
}
