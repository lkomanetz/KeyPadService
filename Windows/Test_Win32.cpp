#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <keypad.h>
#include <windowskeyboard.h>
#include <windowsprogram.h>
#include <csignal>

using namespace std;

//TODO(Logan) -> Use signals to end the application gracefully
int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <FILE_LOCATION>" << std::endl;
		return -1;
	}

	WindowsProgram* program = new WindowsProgram(argv[1]);
	WindowsJoystick* js = program->getJoystick();

	program->start();
	while (true) {
		if (!js->isActive()) {
			cerr << "No controller connected..." << endl;
			break;
		}
		Sleep(25);
	}

	delete program;
	return 0;
}