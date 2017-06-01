#include <iostream>
#if PLATFORM_LINUX
#include <linuxprogram.h>
#include <linuxprocess.h>
#elif PLATFORM_WINDOWS
#include <windowsprogram.h>
#include <windowsprocess.h>
#endif

int main (int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <FILE_LOCATION>" << std::endl;
	}

	Program* program = NULL;
	Process* process = NULL;

#if PLATFORM_LINUX
	process = new LinuxProcess();
	program = new LinuxProgram(argv[1]);
#elif PLATFORM_WINDOWS
	process = new WindowsProcess();
	program = new WindowsProgram(argv[1]);
#endif

	process->start();
	program->run();

	delete process;
	delete program;
	process = NULL;
	program = NULL;

	return 0;
}