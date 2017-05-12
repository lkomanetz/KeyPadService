#include <linuxprogram.h>
#include <iostream>

LinuxProgram::LinuxProgram(char* fileLocation) :
	Program(fileLocation) {

	_fd = open("dev/input/event4", O_RDWR | O_NONBLOCK);
	p_joystick = new LinuxJoystick();
	p_joystick->buttonPressed = [&](ControllerButton btn) {
		sendKeyEvent(btn, 1);
	};
	p_joystick->buttonReleased = [&](ControllerButton btn) {
		sendKeyEvent(btn, 0);
	};
}

LinuxProgram::~LinuxProgram() {
	Program::isRunning = false;
	pthread_join(_jsStateThread, NULL);
	pthread_cancel(_jsStateThread);
	XCloseDisplay(p_display);
	ioctl(_fd, UI_DEV_DESTROY);
	close(_fd);
}

void LinuxProgram::start() {
	pthread_create(
		&_jsStateThread,
		NULL,
		&LinuxProgram::getJoystickState,
		this
	);
}

LinuxJoystick* LinuxProgram::getJoystick() const {
	return dynamic_cast<LinuxJoystick*>(p_joystick);
}

void* LinuxProgram::getJoystickState(void* obj) {
	LinuxProgram* program = reinterpret_cast<LinuxProgram*>(obj);
	Joystick* js = program->getJoystick();
	KeyMapping* keyMap = program->getKeyMap();

	while (Program::isRunning) {
		js->fillState();
		usleep(1);
	}
}

void LinuxProgram::sendKeyEvent(KeyboardButton button, short keyEvent) {
	int n = 0;
	input_event evt;
	evt.type = EV_KEY;
	evt.value = keyEvent;
	evt.code = KEY_A;
	n = write(_fd, &evt, sizeof(input_event));
	if (n < 0) {
		std::cout << "Failed to write keypress" << std::endl;
	}
	else {
		evt.type = EV_SYN;
		evt.code = 0;
		evt.value = 0;
		write(_fd, &evt, sizeof(input_event));
	}

	/*
	evt.value = 0;
	evt.code = KEY_A;
	gettimeofday(&evt.time, 0);
	n = write(fd, &evt, sizeof(input_event));
	*/
	// std::cout << "done" << std::endl;
	/*
	/*
	XKeyEvent evt = {};
	evt.display = p_display;
	evt.window = _focusedWindow;
	evt.root = _rootWindow;
	evt.subwindow = None;
	evt.time = CurrentTime;
	evt.x = 1;
	evt.y = 1;
	evt.x_root = 1;
	evt.y_root = 1;
	evt.same_screen = True;
	evt.keycode = XKeysymToKeycode(p_display, XK_a);
	evt.state = 0;
	evt.type = KeyPress;

	XSendEvent(evt.display, evt.window, True, KeyPressMask, (XEvent*)&evt);
	evt.type = KeyRelease;
	XSendEvent(evt.display, evt.window, True, KeyPressMask, (XEvent*)&evt);
	*/
}

void LinuxProgram::getCurrentFocusedWindow() {
	if (p_display != NULL)
		XCloseDisplay(p_display);

	p_display = XOpenDisplay(0);
	if (p_display == NULL) {
		std::cout << "NO DISPLAY" << std::endl;
		return;
	}
	_rootWindow = XDefaultRootWindow(p_display);
	int revert;
	XGetInputFocus(p_display, &_focusedWindow, &revert);
}