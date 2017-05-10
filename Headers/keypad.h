#ifndef KEYPAD_H
#define KEYPAD_H

#include <string>
#include <fstream>
#include <keybindconverter.h>
#include <keymapping.h>
#include <joystick.h>

#define FILE_LOCATION "keybindings.txt"

using namespace std;


class Program {
private:
	KeyMapping _keyMap;

	void loadKeyMap(string fileLoc);

protected:
	Joystick* p_joystick;

public:
	Program();
	Program(char* fileLocation);
	virtual ~Program();
	static bool isRunning;
	KeyMapping* getKeyMap() { return &_keyMap; }
	void setKeyMap(KeyMapping map) { _keyMap = map; }
	virtual void sendKeyPress(KeyboardButton button) = 0;
	virtual void start() = 0;
	virtual Joystick* getJoystick() const { return p_joystick; }
};

#endif
