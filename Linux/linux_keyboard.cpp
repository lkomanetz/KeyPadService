#include <linuxkeyboard.h>

void LinuxKeyboard::sendKeyPress(KeyboardButton* buttons) {
	int n = this->writeToInputBuffer(buttons);
	if (n < 0) {
		std::cout << "Failed to write keypress" << std::endl;
	}
	else {
		evt.type = EV_SYN;
		evt.code = 0;
		evt.value = 0;
		write(_fd, &evt, sizeof(input_event));
	}
}

void LinuxKeyboard::sendKeyRelease(KeyboardButton* buttons) {
	int n = this->writeToInputBuffer(buttons);
	if (n < 0) {
		std::cout << "Failed to write keypress" << std::endl;
	}
	else {
		evt.type = EV_SYN;
		evt.code = 0;
		evt.value = 0;
		write(_fd, &evt, sizeof(input_event));
	}
}

//TODO(Logan)-> Remove the hard-coded KEY_A usage.
int LinuxKeyboard::writeToInputBuffer(KeyboardButton* button) {
	input_event evt;
	evt.type = EV_KEY;
	evt.value = KeyboardEvents::KEY_RELEASE;
	evt.code = KEY_A;
	return write(_fd, &evt, sizeof(input_event));
}