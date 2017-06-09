#include <string>
#include <iostream>
#include <consolelogger.h>
#if PLATFORM_LINUX
#include <linuxprogram.h>
#include <linuxprocess.h>
#elif PLATFORM_WINDOWS
#include <windowsprogram.h>
#include <windowsprocess.h>
#endif

int main (int argc, char** argv) {
	ConsoleLogger logger;
	if (argc != 2) {
		std::string msg = "Usage: ";
		msg.append(argv[0]);
		msg.append(" <FILE_LOCATION>");
		logger.log(msg);
	}

	Program* program = NULL;
	Process* process = NULL;

#if PLATFORM_LINUX
	process = new LinuxProcess(&logger);
	program = new LinuxProgram(argv[1], &logger);
#elif PLATFORM_WINDOWS
	process = new WindowsProcess();
	program = new WindowsProgram(argv[1]);
#endif

	process->start();
	program->run();
	process->stop();

	delete process;
	delete program;
	process = NULL;
	program = NULL;

	return 0;
}