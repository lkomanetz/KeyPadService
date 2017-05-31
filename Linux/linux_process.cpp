#include <linuxprocess.h>

LinuxProcess::LinuxProcess(Program* program) {
	_program = program;
}

LinuxProcess::~LinuxProcess() {
	delete _program;
	_program = NULL;
}

void LinuxProcess::start() {
}

void LinuxProcess::stop() {}