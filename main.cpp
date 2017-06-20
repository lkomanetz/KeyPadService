#include <string>
#include <consolelogger.h>
#include <csignal>
#include <iostream>

#if PLATFORM_LINUX
#include <linuxkeypad.h>
#elif PLATFORM_WINDOWS
#include <windowskeypad.h>

#endif

// TODO(Logan) -> I need to get rid of this preprocessor because it's bad composition.
#if PLATFORM_WINDOWS
BOOL winSignalHandler(DWORD signalNum);
#endif

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
	delete program;
	program = NULL;

	exit(signalNum);
}

// TODO(Logan) -> I really need to refactor this.  I shouldn't need this preprocessor.
#if PLATFORM_WINDOWS
BOOL WINAPI winSignalHandler(DWORD signal) {
	if (signal == CTRL_C_EVENT || signal == CTRL_CLOSE_EVENT) {
		Program::isRunning = false;
		return TRUE;
	}

	return FALSE;
}
#endif