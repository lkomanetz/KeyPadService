#include <stdexcept>
#include <exception>
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
	ConsoleLogger logger;
	try {
		Settings settings;
		settings.load();
		program = getProgramForPlatform(settings.getKeybindingsLocation().c_str(), &logger);
		program->run();
	}
	catch (std::exception& ex) {
		logger.log(ex.what());
	}
	catch (...) {
		logger.log("Unknown exception occurred");
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
	throw std::runtime_exception("Unsupported platform");
#endif
}