#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <keypad.h>
#include <windowskeyboard.h>
#include <windowsprogram.h>

using namespace std;

void testKbInput();
KeyMapping buildMap();

int main(int argc, char** argv) {
	WindowsProgram* program = new WindowsProgram();
	program->setKeyMap(buildMap());
	WindowsJoystick* js = program->getJoystick();

	while (true) {
		if (!js->isActive())
			break;
	}

	delete program;

	// testKbInput();
	return 0;
}

KeyMapping buildMap() {
	KeyMapping map;
	for (int i = 0; i < 4; ++i) {
		KeyBind bind;
		bind.source = i;
		switch (i) {
			case 0:
				bind.destination = 0x41; // A Key
				break;
			case 1:
				bind.destination = 0x42; // B Key
				break;
			case 2:
				bind.destination = 0x43; // C Key
				break;
			case 3:
				bind.destination = 0x44; // D Key
				break;
		}

		map.addBinding(bind);
	}
	return map;
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