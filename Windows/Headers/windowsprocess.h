#ifndef WINDOWSPROCESS_H
#define WINDOWSPROCESS_H

#include <process.h>
#include <messagelogger.h>
#include <Windows.h>

#define SERVICE_NAME "KeyPad"

class WindowsProcess : public Process {
private:
	MessageLogger* p_logger;
	static SERVICE_STATUS _serviceStatus;
	static SERVICE_STATUS_HANDLE _statusHandle;
	static HANDLE _serviceStopEvent;

	static void WINAPI serviceMain(DWORD argc, LPSTR *argv);
	static void WINAPI serviceCtrlHandler(DWORD controlCode);

public:
	WindowsProcess(MessageLogger* pLogger);
	int initialize();
	void start();
	void stop();
};

#endif