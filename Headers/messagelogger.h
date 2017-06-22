#ifndef MESSAGELOGGER_H
#define MESSAGELOGGER_H

#include <string>
#include <ctime>

class MessageLogger {
public:
	virtual void log(const std::string msg) = 0;
};

#endif