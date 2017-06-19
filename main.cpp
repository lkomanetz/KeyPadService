#include <string>
#include <consolelogger.h>
#include <csignal>

#if PLATFORM_LINUX
#include <linuxkeypad.h>
#elif PLATFORM_WINDOWS
#include <windowskeypad.h>

#endif

BOOL winSignalHandler(DWORD signalNum);
void linuxSignalHandler(int signalNum);
void cleanResources();

Program* program = NULL;

int main (int argc, char** argv) {
	ConsoleLogger logger;
	if (argc != 2) {
		std::string msg = "Usage: ";
		msg.append(argv[0]);
		msg.append(" <FILE_LOCATION>");
		logger.log(msg);
	}


#if PLATFORM_LINUX
	program = new LinuxKeypad(argv[1], &logger);
	signal(SIGHUP, linuxSignalHandler);
	signal(SIGINT, linuxSignalHandler);
#elif PLATFORM_WINDOWS
	program = new WindowsKeypad(argv[1], &logger);
	SetConsoleCtrlHandler(winSignalHandler, TRUE);
#endif

	program->run();

	delete program;
	program = NULL;

	return 0;
}

void linuxSignalHandler(int signalNum) {
	Program::isRunning = false;
}

BOOL WINAPI winSignalHandler(DWORD signal) {
	if (signal == CTRL_C_EVENT || signal == CTRL_CLOSE_EVENT) {
		Program::isRunning = false;
		return TRUE;
	}

	return FALSE;
}