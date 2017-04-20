#include <iostream>
#include <Windows.h>
#include <keypad.h>

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {

	KeyMapping keyMap = {};
	keyMap.destination = 1;
	keyMap.source = BUTTON_A;

	Gamepad gp = {};
	gp.aButtonPressed = true;

	if (gp.aButtonPressed) {
		MessageBox(NULL, "A button is pressed", "Test", MB_OK | MB_ICONINFORMATION);
	}
	else {
		MessageBox(NULL, "A button is NOT pressed", "Test", MB_OK | MB_ICONINFORMATION);
	}

	if (keyMap.destination == 1) {
		MessageBox(NULL, "Destination is 1", "Test", MB_OK | MB_ICONINFORMATION);
	}

	if (keyMap.source == BUTTON_A) {
		MessageBox(NULL, "Button is A", "Test", MB_OK | MB_ICONINFORMATION);
	}

	return 0;
}