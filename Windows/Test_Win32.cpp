#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <keypad.h>
#include <windowskeyboard.h>
#include <windowsprogram.h>

using namespace std;

int main(int argc, char** argv) {
	WindowsProgram* program = new WindowsProgram();
	WindowsJoystick* js = program->getJoystick();

	program->start();
	while (true) {
		if (!js->isActive()) {
			cerr << "No controller connected..." << endl;
			break;
		}
	}

	delete program;
	return 0;
}