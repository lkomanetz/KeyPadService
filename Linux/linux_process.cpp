#include <linuxprocess.h>
#include <iostream>

LinuxProcess::LinuxProcess(char* fileLocation) {
	_program = new LinuxProgram(fileLocation);
}

LinuxProcess::~LinuxProcess() {
	delete _program;
	_program = NULL;
}

void LinuxProcess::start() {
	LinuxJoystick* js = _program->getJoystick();
	while(true) {
		if (!js->isActive()) {
			std::cout << "State:  NOT ACTIVE" << std::endl;
			break;
		}

		js->fillState();
		usleep(25);
	}
}

void LinuxProcess::stop() {}