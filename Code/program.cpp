#include <../Headers/program.h>
#include <iostream>

bool Program::isRunning = false;

Program::Program() {
	Program::isRunning = true;
	p_joystick = NULL;
}

Program::Program(char* fileLocation, MessageLogger* pLogger) : Program() {
	p_logger = pLogger;
	//TODO(Logan) -> Figure out why not finding the keybindings file causes weird behavior.
	loadKeyMap(fileLocation);
	pLogger->log("KeyPad service running...");
}

Program::~Program() {
	if (p_joystick) {
		delete p_joystick;
	}

	if (p_keyboard) {
		delete p_keyboard;
	}
	p_logger->log("KeyPad service stopped...");
}

void Program::loadKeyMap(string fileLoc) {
	_keyMap = {};

	ifstream inFile(fileLoc.c_str());
	if (!inFile) {
		std::string errorMsg = "Unable to open file '";
		errorMsg.append(fileLoc);
		errorMsg.append("'");
		throw errorMsg.c_str();
	}

	string line;
	while (getline(inFile, line)) {
		if (line.length() == 0) {
			continue;
		}

		KeyBind bind = KeyBindConverter::toKeyBind(line);
		_keyMap.addBinding(bind);
	}

}