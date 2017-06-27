#include <../Headers/program.h>
#include <iostream>

bool Program::isRunning = false;

Program::Program() {
	Program::isRunning = true;
	p_joystick = NULL;
}

Program::Program(char* fileLocation, MessageLogger* pLogger) : Program() {
	p_logger = pLogger;
	p_logger->log("Attempting to start service...");

	int returnCode = loadKeyMap(fileLocation);
	if (returnCode == -1) {
		std::string msg = "Unable to load '";
		msg.append(fileLocation);
		msg.append("'");
		throw msg.c_str();
	}

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

int Program::loadKeyMap(string fileLoc) {
	_keyMap = {};

	ifstream inFile(fileLoc.c_str());
	if (!inFile) {
		return -1;
	}

	string line;
	while (getline(inFile, line)) {
		if (line.length() == 0) {
			continue;
		}

		KeyBind bind = KeyBindConverter::toKeyBind(line);
		_keyMap.addBinding(bind);
	}

	return 0;
}