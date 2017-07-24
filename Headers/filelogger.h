#ifndef FILELOGGER_H
#define FILELOGGER_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <messagelogger.h>

class FileLogger : public MessageLogger {
private:
	const char* _fileLocation;

public:
	FileLogger(const char* fileLocation);
	virtual void log(std::string msg);
};

#endif