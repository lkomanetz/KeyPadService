#ifndef MESSAGELOGGER_H
#define MESSAGELOGGER_H

#include <string>

class MessageLogger {
public:
	virtual void log(const std::string msg) = 0;
};

#endif