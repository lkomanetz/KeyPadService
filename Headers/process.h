#ifndef PROCESS_H
#define PROCESS_H

class Process {
public:
	virtual int initialize() = 0;
	virtual void start() = 0;
	virtual void stop() = 0;

};

#endif