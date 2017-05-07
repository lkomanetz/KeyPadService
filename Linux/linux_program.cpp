#include <linuxprogram.h>
#include <iostream>

LinuxProgram::LinuxProgram() {
	// this->getCurrentFocusedWindow();
	p_joystick = new LinuxJoystick();
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
		Joystick_State state = js->getCurrentState();
		KeyboardButton kb;

		if (js->isButtonPressed(ControllerButtons::DPAD_LEFT)) {
			std::cout << "Left dpad pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::DPAD_RIGHT)) {
			std::cout << "Right dpad pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::DPAD_UP)) {
			std::cout << "Up dpad pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::DPAD_DOWN)) {
			std::cout << "Down dpad pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::A_BUTTON)) {
			kb = keyMap->getKeyboardButtonFor(ControllerButtons::A_BUTTON);
			program->sendKeyPress(kb);
			// std::cout << "A button maps to '" << kb << "'" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::B_BUTTON)) {
			kb = keyMap->getKeyboardButtonFor(ControllerButtons::B_BUTTON);
			std::cout << "B button maps to '" << kb << "'" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::X_BUTTON)) {
			kb = keyMap->getKeyboardButtonFor(ControllerButtons::X_BUTTON);
			std::cout << "X button maps to '" << kb << "'" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::Y_BUTTON)) {
			kb = keyMap->getKeyboardButtonFor(ControllerButtons::Y_BUTTON);
			std::cout << "Y button maps to '" << kb << "'" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::LEFT_SHOULDER_BUTTON)) {
			std::cout << "Left shoulder button pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::RIGHT_SHOULDER_BUTTON)) {
			std::cout << "Right shoulder button pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::LEFT_STICK_BUTTON)) {
			std::cout << "Left stick pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::RIGHT_STICK_BUTTON)) {
			std::cout << "Right stick pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::BACK_BUTTON)) {
			std::cout << "Back button pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::MENU_BUTTON)) {
			std::cout << "Menu button pressed" << std::endl;
		}
		else if (js->isButtonPressed(ControllerButtons::HOME_BUTTON)) {
			std::cout << "Home button pressed" << std::endl;
		}
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