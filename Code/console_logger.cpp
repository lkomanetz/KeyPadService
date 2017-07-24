#include <consolelogger.h>

void ConsoleLogger::log(std::string msg) {
	std::cout << this->getCurrentLocalTime() << " -> " << msg.c_str() << std::endl;
}