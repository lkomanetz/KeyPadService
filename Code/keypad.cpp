#include <../Headers/keypad.h>

bool Program::isRunning = false;

Program::Program() {
	Program::isRunning = true;
	p_joystick = NULL;
}

Program::Program(char* fileLocation) : Program() {
	loadKeyMap(fileLocation);
}

Program::~Program() {
	if (p_joystick) {
		delete p_joystick;
	}

	if (p_keyboard) {
		delete p_keyboard;
	}
}

void Program::loadKeyMap(string fileLoc) {
	_keyMap = {};

	ifstream inFile(fileLoc);
	if (!inFile) {
		return;
	}

	while (inFile) {
		string line;
		getline(inFile, line);

		if (line.length() == 0) {
			continue;
		}

		KeyBind bind = KeyBindConverter::toKeyBind(line);
		_keyMap.addBinding(bind);
	}

}