#include <linuxkeypad.h>

LinuxKeypad::LinuxKeypad(char* fileLocation, MessageLogger* pLogger) :
	Program(fileLocation, pLogger) {

	p_keyboard = new LinuxKeyboard(p_logger);
	p_joystick = new LinuxJoystick(p_logger);


	this->initializeJoystickEvents();
	this->setupSignalHandler();
}

LinuxKeypad::~LinuxKeypad() {
	Program::isRunning = false;
}

LinuxJoystick* LinuxKeypad::getJoystick() const {
	return dynamic_cast<LinuxJoystick*>(p_joystick);
}

void LinuxKeypad::run() {
	int connectAttempts = 0;
	LinuxJoystick* js = this->getJoystick();
	js->connect();

	while(Program::isRunning) {
		if (!js->isActive()) {
			js->connect();
			connectAttempts++;
		}

		if (js->isActive()) {
			js->fillState();
		}
		else if (!js->isActive() && connectAttempts >= 5) {
			throw exception("Joystick connect attempt threshold met");
		}
		this->sleep(25);
	}
}

void LinuxKeypad::sleep(int sleepMs) {
	usleep(sleepMs);
}

void LinuxKeypad::setupSignalHandler() {
	signal(SIGHUP, LinuxKeypad::signalHandler);
	signal(SIGINT, LinuxKeypad::signalHandler);
}

void LinuxKeypad::signalHandler(int signalNum) {
	Program::isRunning = false;	
}

void LinuxKeypad::initializeJoystickEvents() {
	p_joystick->buttonPressed = [&](ControllerButton btn) {
		KeyboardButton* kbBtn = getKeyMap()->getKeyboardButtonFor(btn);
		p_keyboard->sendKeyPress(getKeyMap()->getKeyboardButtonFor(btn));
	};
	p_joystick->buttonReleased = [&](ControllerButton btn) {
		KeyboardButton* kbBtn = getKeyMap()->getKeyboardButtonFor(btn);
		p_keyboard->sendKeyRelease(getKeyMap()->getKeyboardButtonFor(btn));
	};
}