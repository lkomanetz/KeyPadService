#include <linuxkeyboard.h>
#include <iostream>

LinuxKeyboard::LinuxKeyboard() {
	_fd = open("/dev/input/event4", O_RDWR | O_NONBLOCK);
	if (_fd == -1) {
		std::cerr << "Failed to open dev/input/event4" << std::endl;
	}
}

LinuxKeyboard::~LinuxKeyboard() {
	close(_fd);	
}

void LinuxKeyboard::sendKeyPress(KeyboardButton* buttons) {
	int n = this->writeToInputBuffer(buttons, KeyboardEvents::KEY_PRESS);
	if (n < 0) {
		std::cout << "Failed to write keypress" << std::endl;
	}
	else {
		input_event evt;
		evt.type = EV_SYN;
		evt.code = 0;
		evt.value = 0;
		write(_fd, &evt, sizeof(input_event));
	}
}

void LinuxKeyboard::sendKeyRelease(KeyboardButton* buttons) {
	int n = this->writeToInputBuffer(buttons, KeyboardEvents::KEY_RELEASE);
	if (n < 0) {
		std::cout << "Failed to write keypress" << std::endl;
	}
	else {
		input_event evt;
		evt.type = EV_SYN;
		evt.code = 0;
		evt.value = 0;
		write(_fd, &evt, sizeof(input_event));
	}
}

//TODO(Logan)-> Remove the hard-coded KEY_A usage.
int LinuxKeyboard::writeToInputBuffer(KeyboardButton* button, int kbEvent) {
	input_event evt;
	evt.type = EV_KEY;
	evt.value = kbEvent;
	evt.code = *button;
	return write(_fd, &evt, sizeof(input_event));
}