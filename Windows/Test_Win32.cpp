#include <iostream>
#include <windows.h>
#include <keypad.h>
#include <windowsprogram.h>

using namespace std;

int main(int argc, char** argv) {
	WindowsProgram* program = new WindowsProgram();
	WindowsJoystick* js = program->getJoystick();

	while (true) {
		Sleep(1000);
		if (!js->isActive())
			break;
	}

	delete program;
	return 0;
}