#include <string>
#include <consolelogger.h>
#include <filelogger.h>
#include <settings.h>

#if PLATFORM_LINUX
#include <linuxkeypad.h>
#elif PLATFORM_WINDOWS
#include <windowskeypad.h>

#endif

Program* getProgramForPlatform(const char* keybindingsLoc, MessageLogger* pLogger);

Program* program = NULL;

int main (int argc, char** argv) {
	FileLogger logger("test.txt");
	try {
		Settings settings;
		settings.load();
		program = getProgramForPlatform(settings.getKeybindingsLocation().c_str(), &logger);
		program->run();
	}
	catch (const char* ex) {
		logger.log(ex);
	}

	if (program) {
		delete program;
		program = NULL;
	}

	return 0;
}

Program* getProgramForPlatform(const char* keybindingsLoc, MessageLogger* pLogger) {
#if PLATFORM_LINUX
	return new LinuxKeypad(const_cast<char*>(keybindingsLoc), pLogger);
#elif PLATFORM_WINDOWS
	return new WindowsKeypad(const_cast<char*>(keybindingsLoc), pLogger);
#else
	throw "Unsupported platform...";
#endif

}