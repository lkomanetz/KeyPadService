#ifndef WINDOWSPROCESS_H
#define WINDOWSPROCESS_H

#include <process.h>
#include <messagelogger.h>
#include <windows.h>

class WindowsProcess : public Process {
private:
	MessageLogger* p_logger;

public:
	WindowsProcess(MessageLogger* pLogger);
	void start();
	void stop();
};

#endif