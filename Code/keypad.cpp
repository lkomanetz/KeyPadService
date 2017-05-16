#include <../Headers/keypad.h>
#include <iostream>

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

	ifstream inFile(fileLoc.c_str());
	if (!inFile) {
		std::cerr << "Unable to open file '" << fileLoc << "'" << std::endl;
		return;
	}

	while (inFile) {
		string line;
		getline(inFile, line);

		if (line.length() == 0) {
			continue;
		}

		//TODO(Logan)-> Make interface for KeyBindConverter since Windows and Linux are different.
		KeyBind bind = KeyBindConverter::toKeyBind(line);
		_keyMap.addBinding(bind);
	}

}