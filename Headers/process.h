#ifndef PROCESS_H
#define PROCESS_H

class Process {
public:
	virtual void start() = 0;
	virtual void stop() = 0;

};

#endif