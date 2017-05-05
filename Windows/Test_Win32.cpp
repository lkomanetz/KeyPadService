#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <keypad.h>
#include <windowskeyboard.h>
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
	WindowsKeyboard* pKb = new WindowsKeyboard();

	for (int i = 0; i < 4; ++i) {
		pKb->sendKeyPress(&right);
		pKb->sendKeyRelease(&right);
		Sleep(1000);
	}

	delete pKb;
	pKb = NULL;
}