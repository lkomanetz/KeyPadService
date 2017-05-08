#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <keypad.h>
#include <windowskeyboard.h>
#include <windowsprogram.h>

using namespace std;

KeyMapping buildMap();

int main(int argc, char** argv) {
	WindowsProgram* program = new WindowsProgram();
	program->setKeyMap(buildMap());
	WindowsJoystick* js = program->getJoystick();

	program->start();
	while (true) {
		if (!js->isActive()) {
			cout << "No controller connected..." << endl;
			break;
		}
	}

	delete program;
	return 0;
}

//TODO(Logan)->I want to be able to load a binding profile from the file system.
KeyMapping buildMap() {
	KeyMapping map;
	for (int i = 0; i < 15; ++i) {
		KeyBind bind {};
		bind.source = i;
		switch (i) {
			case 0:
				bind.destination = 0x5A; // Z Key
				break;
			case 2:
				bind.destination = 0x58; // X Key
				break;
			case 6:
				bind.destination = 0x20; // Space bar
				break;
			case 7:
				bind.destination = 0x0D; // Enter
				break;
			case 11:
				bind.destination = 0x27; // Right-arrow
				break;
			case 12:
				bind.destination = 0x25; // Left-arrow
				break;
			case 13:
				bind.destination = 0x26; // Up-arrow
				break;
			case 14:
				bind.destination = 0x28; // Down-arrow
				break;
		}

		if (bind.destination != 0) {
			map.addBinding(bind);
		}
	}
	return map;
}