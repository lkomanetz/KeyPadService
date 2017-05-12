#include <cstdio>
#include <iostream>
#include <assert.h>
#include <linuxprogram.h>

using namespace std;

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <FILE_LOCATION>" << std::endl;
		return -1;
	}

	LinuxProgram* p = new LinuxProgram(argv[1]);
	LinuxJoystick* js = p->getJoystick();

	p->start();
	while (true) {
		if (!js->isActive()) {
			cout << "State:  NOT ACTIVE" << endl;
			break;
		}
		usleep(1);
	}

	delete p;
	return 0;
}