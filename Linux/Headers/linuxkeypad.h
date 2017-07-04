#ifndef LINUXKEYPAD_H
#define LINUXKEYPAD_H

#include <csignal>
#include <linuxjoystick.h>
#include <linuxkeyboard.h>
#include <../../Headers/program.h>

class LinuxKeypad : public Program {
private:
	static void signalHandler(int signalNum);
	static void* getJoystickState(void*);

	void initializeJoystickEvents();

protected:
	void setupSignalHandler();

public:
	LinuxKeypad(char* fileLocation, MessageLogger* pLogger);
	virtual ~LinuxKeypad();
	virtual LinuxJoystick* getJoystick() const;
	virtual void sendKeyPress(KeyboardButton btn) {}
	virtual void sleep(int sleepMs);
	virtual void run();
	void getCurrentFocusedWindow();
};

#endif