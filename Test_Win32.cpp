#include <iostream>
#include <Windows.h>

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {

	Gamepad gp = {};
	gp.aButtonPressed = true;

	if (gp.aButtonPressed) {
		MessageBox(NULL, "A button is pressed", "Test", MB_OK | MB_ICONINFORMATION);
	}
	else {
		MessageBox(NULL, "A button is NOT pressed", "Test", MB_OK | MB_ICONINFORMATION);
	}

	return 0;
}

