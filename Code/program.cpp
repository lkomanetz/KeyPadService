#include <../Headers/program.h>

bool Program::isRunning = false;

Program::Program() {
	Program::isRunning = true;
	p_joystick = NULL;
}

Program::Program(char* fileLocation, MessageLogger* pLogger) : Program() {
	p_logger = pLogger;
	p_logger->log("Attempting to start service");

	loadKeyMap(fileLocation);
	pLogger->log("KeyPad service running");
}

Program::~Program() {
	if (p_joystick) {
		delete p_joystick;
		p_joystick = NULL;
	}

	if (p_keyboard) {
		delete p_keyboard;
		p_keyboard = NULL;
	}
	p_logger->log("KeyPad service stopped");
}

void Program::loadKeyMap(string fileLoc) {
	_keyMap = {};

	ifstream inFile(fileLoc.c_str());
	if (!inFile) {
		throw std::runtime_error("Unable to load '" + fileLoc + "'");
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