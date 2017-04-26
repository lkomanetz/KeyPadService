#ifndef LINUXPROGRAM_H
#define LINUXPROGRAM_H

#include <pthread.h>
#include <linuxjoystick.h>
#include <../../Headers/keypad.h>

class LinuxProgram : public Program {
private:
	pthread_t _jsStateThread;
	static void* getJoystickState(void*);
	bool _exitThread;

public:
	LinuxProgram();
	~LinuxProgram();
	virtual LinuxJoystick* getJoystick() const;
};

#endif
