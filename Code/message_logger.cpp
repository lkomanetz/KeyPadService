#include <messagelogger.h>
#include <iostream>

const char* MessageLogger::getCurrentLocalTime() {
	time_t now = std::time(0);
	_currentDateTimeStr = std::ctime(&now);
	std::size_t index = _currentDateTimeStr.find('\n');

	if (index != -1) {
		_currentDateTimeStr.erase(index, 1);	
	}

	return _currentDateTimeStr.c_str();
}