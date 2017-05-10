#include <linuxprogram.h>
#include <iostream>

LinuxProgram::LinuxProgram(char* fileLocation) :
	Program(fileLocation) {
	// this->getCurrentFocusedWindow();
	p_joystick = new LinuxJoystick();
	p_joystick->buttonPressed = [&](ControllerButton btn) {
		std::cout << btn << " button is pressed" << std::endl;
	}
	p_joystick->buttonReleased = [&](ControllerButton btn) {
		std::cout << btn << " button was released" << std::endl;
	}
}

LinuxProgram::~LinuxProgram() {
	Program::isRunning = false;
	pthread_join(_jsStateThread, NULL);
	pthread_cancel(_jsStateThread);
	XCloseDisplay(p_display);
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
	}
}

void LinuxProgram::sendKeyPress(KeyboardButton button) {
	int n = 0;
	int fd = open("/dev/input/event4", O_RDWR | O_NONBLOCK);
	if (fd == -1) {
		std::cout << "Unable to open keyboard socket" << std::endl;
		return;
	}
	input_event evt;
	evt.type = EV_KEY;
	evt.value = 1;
	evt.code = KEY_A;
	gettimeofday(&evt.time, 0);
	n = write(fd, &evt, sizeof(input_event));

	evt.value = 0;
	evt.code = KEY_A;
	gettimeofday(&evt.time, 0);
	n = write(fd, &evt, sizeof(input_event));
	close(fd);
	std::cout << "done" << std::endl;
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
	p_display = XOpenDisplay(0);
	if (p_display == NULL) {
		std::cout << "NO DISPLAY" << std::endl;
		return;
	}
	_rootWindow = XDefaultRootWindow(p_display);
	int revert;
	XGetInputFocus(p_display, &_focusedWindow, &revert);
}