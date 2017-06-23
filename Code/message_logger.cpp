#include <messagelogger.h>

const char* MessageLogger::getCurrentLocalTime() {
	time_t now = time(0);
	std::string dateTimeStr = std::string(ctime(&now));
	std::size_t index = dateTimeStr.find('\n');
	dateTimeStr.erase(index, 1);	
	return dateTimeStr.c_str();
}