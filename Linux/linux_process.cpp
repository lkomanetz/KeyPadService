#include <linuxprocess.h>

LinuxProcess::LinuxProcess(MessageLogger* pLogger) {
	p_logger = pLogger;
}

void LinuxProcess::start() {
	p_logger->log("KeyPad process started...");
}

void LinuxProcess::stop() {
	p_logger->log("KeyPad process stopped...");
}