#ifndef LINUXPROCESS_H
#define LINUXPROCESS_H

#include <process.h>

class LinuxProcess : public Process {
public:
	LinuxProcess();
	void start();
	void stop();

};

#endif