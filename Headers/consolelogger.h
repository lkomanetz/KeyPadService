#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include <iostream>
#include <algorithm>
#include <messagelogger.h>

class ConsoleLogger : public MessageLogger {
private:
	const char* getCurrentLocalTime();

public:
	virtual void log(std::string msg);

};

#endif