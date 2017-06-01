#ifndef WINDOWSPROCESS_H
#define WINDOWSPROCESS_H

#include <process.h>

class WindowsProcess : public Process {
public:
	WindowsProcess() {}
	void start() {}
	void stop() {}
};

#endif