#ifndef WINDOWSPROCESS_H
#define WINDOWSPROCESS_H

#include <process.h>
#include <messagelogger.h>
#include <Windows.h>

#define SERVICE_NAME "KeyPad"

class WindowsProcess : public Process {
private:
	MessageLogger* p_logger;
	SERVICE_STATUS _serviceStatus;
	SERVICE_STATUS_HANDLE _statusHandle;
	HANDLE _serviceStopEvent;

	static void WINAPI serviceMain(DWORD argc, LPSTR *argv);

public:
	WindowsProcess(MessageLogger* pLogger);
	int initialize();
	void start();
	void stop();
};

#endif