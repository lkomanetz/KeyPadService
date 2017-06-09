#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include <iostream>
#include <messagelogger.h>

class ConsoleLogger : public MessageLogger {
public:
	virtual void log(std::string msg);

};

#endif