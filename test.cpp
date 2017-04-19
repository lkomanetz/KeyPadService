#include <iostream>
#include <Windows.h>

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {

	MessageBox(NULL, "This is a test", "Test", MB_OK | MB_ICONINFORMATION);
	return 0;

}

