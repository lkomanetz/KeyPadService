#include <filelogger.h>
#include <iostream>

FileLogger::FileLogger(const char* fileLocation) {
	_fileLocation = fileLocation;
}

void FileLogger::log(std::string msg) {
	std::ofstream outFile(_fileLocation, std::ios::app);
	if (!outFile) {
		return;
	}

	outFile << this->getCurrentLocalTime() << " -> " <<  msg << std::endl;
}