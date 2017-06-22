#include <consolelogger.h>

void ConsoleLogger::log(std::string msg) {
	std::cout << this->getCurrentLocalTime() << " -> " << msg.c_str() << std::endl;
}

const char* ConsoleLogger::getCurrentLocalTime() {
	time_t now = time(0);
	std::string dateTimeStr = std::string(ctime(&now));
	std::size_t index = dateTimeStr.find('\n');
	dateTimeStr.erase(index, 1);	
	return dateTimeStr.c_str();
}