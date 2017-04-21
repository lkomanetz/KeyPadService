#include <iostream>
#include <Windows.h>
#include <keypad.h>

const ControllerButton DPAD_UP = 0x0001;
const ControllerButton DPAD_DOWN = 0x0002;
const ControllerButton DPAD_LEFT = 0x0004;
const ControllerButton DPAD_RIGHT = 0x0008;
const ControllerButton START = 0x0010;
const ControllerButton BACK = 0x0020;
const ControllerButton LEFT_THUMBSTICK = 0x0040;
const ControllerButton RIGHT_THUMBSTICK = 0x0080;
const ControllerButton LEFT_SHOULDER = 0x0100;
const ControllerButton RIGHT_SHOULDER = 0x0200;
const ControllerButton BUTTON_A = 0x1000;
const ControllerButton BUTTON_B = 0x2000;
const ControllerButton BUTTON_X = 0x4000;
const ControllerButton BUTTON_Y = 0x8000;

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {

	KeyBind keyMap = {};
	keyMap.destination = 1;
	keyMap.source = BUTTON_A;

	if (keyMap.destination == 1) {
		MessageBox(NULL, "Destination is 1", "Test", MB_OK | MB_ICONINFORMATION);
	}

	if (keyMap.source == BUTTON_A) {
		MessageBox(NULL, "Button is A", "Test", MB_OK | MB_ICONINFORMATION);
	}

	return 0;
}