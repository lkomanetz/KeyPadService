#include <cstdio>
#include <iostream>
#include <keypad.h>

int main(int argc, char** argv) {
	using namespace std;

	Gamepad gp = {};
	gp.aButtonPressed = true;

	if (gp.aButtonPressed) {
		cout << "A is pressed" << endl;
	}
	else {
		cout << "B is pressed" << endl;
	}
}