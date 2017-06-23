#ifndef MESSAGELOGGER_H
#define MESSAGELOGGER_H

#include <string>
#include <ctime>

class MessageLogger {
protected:
	const char* getCurrentLocalTime();

public:
	virtual void log(const std::string msg) = 0;
};

#endif