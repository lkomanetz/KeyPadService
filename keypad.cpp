#include <string>
#include <consolelogger.h>
#include <filelogger.h>

#if PLATFORM_LINUX
#include <linuxkeypad.h>
#elif PLATFORM_WINDOWS
#include <windowskeypad.h>

#endif

Program* program = NULL;

int main (int argc, char** argv) {
	FileLogger logger("test.txt");
	if (argc != 2) {
		std::string msg = "Usage: ";
		msg.append(argv[0]);
		msg.append(" <FILE_LOCATION>");
		logger.log(msg);
	}


#if PLATFORM_LINUX
	program = new LinuxKeypad(argv[1], &logger);
#elif PLATFORM_WINDOWS
	program = new WindowsKeypad(argv[1], &logger);
#endif

	program->run();

	delete program;
	program = NULL;

	return 0;
}