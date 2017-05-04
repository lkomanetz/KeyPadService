#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <keypad.h>
#include <windowsprogram.h>

using namespace std;

void testKbInput();

int main(int argc, char** argv) {
	/*
	WindowsProgram* program = new WindowsProgram();
	WindowsJoystick* js = program->getJoystick();

	while (true) {
		Sleep(1000);
		if (!js->isActive())
			break;
	}

	delete program;
	*/

	testKbInput();
	return 0;
}

/*
 * The whole point of this is to see how sending keyboard input works in Windows.  Should give me an idea
 * on how to extract this into a class.
 */
void testKbInput() {
	Sleep(5000);
	KeyboardButton right = 0x41;

	KEYBDINPUT kb = {};
	INPUT input = {};

	kb.wVk = right;
	kb.dwFlags = 0;
	input.type = INPUT_KEYBOARD;
	input.ki = kb;

	// What I'm doing here is seeing how sending two key-down inputs work.
	// This sends to "a" values as expected.
	SendInput(1, &input, sizeof(input));
	SendInput(1, &input, sizeof(input));

	ZeroMemory(&kb, sizeof(KEYBDINPUT));
	ZeroMemory(&input, sizeof(INPUT));

	kb.dwFlags = KEYEVENTF_KEYUP;
	kb.wVk = right;
	input.type = INPUT_KEYBOARD;
	input.ki = kb;

	SendInput(1, &input, sizeof(input));
}