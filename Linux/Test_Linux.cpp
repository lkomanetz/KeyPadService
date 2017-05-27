#include <cstdio>
#include <iostream>
#include <assert.h>
#include <linuxprogram.h>
#include <linuxprocess.h>

using namespace std;

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <FILE_LOCATION>" << std::endl;
		return -1;
	}

	Process* process = new LinuxProcess(argv[1]);
	process->start();
	/*
	LinuxProgram* p = new LinuxProgram(argv[1]);
	LinuxJoystick* js = p->getJoystick();

	while (true) {
		if (!js->isActive()) {
			cout << "State:  NOT ACTIVE" << endl;
			break;
		}

		js->fillState();
		usleep(25);
	}

	delete p;
	*/
	delete process;
	return 0;
}