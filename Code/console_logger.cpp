#include <consolelogger.h>

void ConsoleLogger::log(std::string msg) {
	std::cout << msg.c_str() << std::endl;
}