#include <windowsprocess.h>

SERVICE_STATUS WindowsProcess::_serviceStatus = {0};
SERVICE_STATUS_HANDLE WindowsProcess::_statusHandle = NULL;
HANDLE WindowsProcess::_serviceStopEvent = INVALID_HANDLE_VALUE;

WindowsProcess::WindowsProcess(MessageLogger* pLogger) {
	p_logger = pLogger;
}

int WindowsProcess::initialize() {
	p_logger->log("Initializing process...");
	SERVICE_TABLE_ENTRY serviceTbl[] = {
		{ SERVICE_NAME, (LPSERVICE_MAIN_FUNCTION) &WindowsProcess::serviceMain },
		{ NULL, NULL }
	};

	if (!StartServiceCtrlDispatcher(serviceTbl)) {
		p_logger->log("Failed to start service dispatcher.");
		return GetLastError();
	}

	return 0;
}

void WindowsProcess::start() {
	if (this->initialize() != 0) {
		return;
	}

	p_logger->log("Starting process...");
}

void WindowsProcess::stop() {
	p_logger->log("Stopping process...");
}

void WINAPI WindowsProcess::serviceMain(DWORD argc, LPSTR* argv) {
	WindowsProcess::_statusHandle = RegisterServiceCtrlHandler(SERVICE_NAME, WindowsProcess::serviceCtrlHandler);
	if (WindowsProcess::_statusHandle == NULL) {
		return;
	}

	SERVICE_STATUS_HANDLE* pStatusHandle = &WindowsProcess::_statusHandle;
	SERVICE_STATUS* pStatus = &WindowsProcess::_serviceStatus;
	
	ZeroMemory(pStatus, sizeof(SERVICE_STATUS));	
	pStatus->dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	pStatus->dwControlsAccepted = 0;
	pStatus->dwCurrentState = SERVICE_START_PENDING;
	pStatus->dwWin32ExitCode = 0;
	pStatus->dwServiceSpecificExitCode = 0;
	pStatus->dwCheckPoint = 0;

	SetServiceStatus(*pStatusHandle, pStatus);
	WindowsProcess::_serviceStopEvent = CreateEvent(NULL, true, false, NULL);

	if (WindowsProcess::_serviceStopEvent == NULL) {
		pStatus->dwControlsAccepted = 0;
		pStatus->dwCurrentState = SERVICE_STOPPED;
		pStatus->dwWin32ExitCode = GetLastError();
		pStatus->dwCheckPoint = 1;

		SetServiceStatus(WindowsProcess::_statusHandle, pStatus);
		return;
	}

	pStatus->dwControlsAccepted = SERVICE_ACCEPT_STOP;
	pStatus->dwCurrentState = SERVICE_RUNNING;
	pStatus->dwWin32ExitCode = 0;
	pStatus->dwCheckPoint = 0;

	SetServiceStatus(WindowsProcess::_statusHandle, pStatus);
	/*
	HANDLE thread = CreateThread(NULL, 0, ServiceWorkerThread, NULL, 0, NULL);
	WaitForSingleObject(thread, INFINITE);
	*/

	CloseHandle(WindowsProcess::_serviceStopEvent);
	pStatus->dwControlsAccepted = 0;
	pStatus->dwCurrentState = SERVICE_STOPPED;
	pStatus->dwWin32ExitCode = 0;
	pStatus->dwCheckPoint = 3;

	SetServiceStatus(WindowsProcess::_statusHandle, pStatus);

}

void WINAPI WindowsProcess::serviceCtrlHandler(DWORD controlCode) {
	switch (controlCode) {
		case SERVICE_CONTROL_STOP:
			if (WindowsProcess::_serviceStatus.dwCurrentState != SERVICE_RUNNING) {
				break;
			}
			WindowsProcess::_serviceStatus.dwControlsAccepted = 0;
			WindowsProcess::_serviceStatus.dwCurrentState = SERVICE_STOP_PENDING;
			WindowsProcess::_serviceStatus.dwWin32ExitCode = 0;
			WindowsProcess::_serviceStatus.dwCheckPoint = 4;

			SetServiceStatus(WindowsProcess::_statusHandle, &WindowsProcess::_serviceStatus);
			SetEvent(WindowsProcess::_serviceStopEvent);
			break;
		default:
			break;
	}
}