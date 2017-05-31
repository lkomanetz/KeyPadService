#ifndef LINUXPROCESS_H
#define LINUXPROCESS_H

#include <process.h>
#include <linuxprogram.h>

class LinuxProcess : public Process {
private:
	LinuxProgram* _program;

public:
	LinuxProcess(Program* program);
	virtual ~LinuxProcess();
	void start();
	void stop();

};

#endif