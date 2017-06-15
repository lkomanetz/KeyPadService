#ifndef LINUXPROCESS_H
#define LINUXPROCESS_H

#include <process.h>
#include <messagelogger.h>

class LinuxProcess : public Process {
private:
	MessageLogger* p_logger;
public:
	LinuxProcess(MessageLogger* pLogger);
	int initialize();
	void start();
	void stop();

};

#endif