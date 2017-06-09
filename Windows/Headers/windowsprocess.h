#ifndef WINDOWSPROCESS_H
#define WINDOWSPROCESS_H

#include <process.h>
#include <messagelogger.h>

class WindowsProcess : public Process {
public:
	WindowsProcess(MessageLogger* pLogger) {}
	void start() {}
	void stop() {}
};

#endif