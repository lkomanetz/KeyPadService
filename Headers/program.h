#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <fstream>
#include <keybindconverter.h>
#include <keymapping.h>
#include <joystick.h>
#include <keyboard.h>
#include <messagelogger.h>

using namespace std;

class Program {
private:
	KeyMapping _keyMap;

	void loadKeyMap(string fileLoc);

protected:
	Joystick* p_joystick;
	Keyboard* p_keyboard;
	MessageLogger* p_logger;

	virtual void setupSignalHandler() = 0;

public:
	Program();
	Program(char* fileLocation, MessageLogger* pLogger);
	virtual ~Program();
	static bool isRunning;
	KeyMapping* getKeyMap() { return &_keyMap; }
	void setKeyMap(KeyMapping map) { _keyMap = map; }
	virtual void sendKeyPress(KeyboardButton button) = 0;
	virtual void sleep(int sleepMs) = 0;
	virtual void run() = 0;
	virtual Joystick* getJoystick() const { return p_joystick; }
};

#endif
