#include <windowsprocess.h>

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

}