#include <linuxkeyboard.h>
#include <iostream>

LinuxKeyboard::LinuxKeyboard(MessageLogger* pLogger, std::string keyboardPortName) :
	Keyboard(pLogger) {
	_fd = open(keyboardPortName, O_RDWR | O_NONBLOCK);
	if (_fd == -1) {
		p_logger->log("Failed to open '" + keyboardPortName + "'.");
	}
}

LinuxKeyboard::~LinuxKeyboard() {
	close(_fd);	
}

void LinuxKeyboard::sendKeyPress(KeyboardButton* buttons) {
	int n = this->writeToInputBuffer(buttons, KeyboardEvents::KEY_PRESS);
	if (n < 0) {
		p_logger->log("Failed to write keypress");
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
		p_logger->log("Failed to write keypress");
	}
	else {
		input_event evt;
		evt.type = EV_SYN;
		evt.code = 0;
		evt.value = 0;
		write(_fd, &evt, sizeof(input_event));
	}
}

int LinuxKeyboard::writeToInputBuffer(KeyboardButton* button, int kbEvent) {
	input_event evt;
	evt.type = EV_KEY;
	evt.value = kbEvent;
	evt.code = *button;
	return write(_fd, &evt, sizeof(input_event));
}