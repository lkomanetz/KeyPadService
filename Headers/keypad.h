#ifndef KEYPAD_H
#define KEYPAD_H

#include <string>
#include <fstream>
#include <keybindconverter.h>
#include <keymapping.h>
#include <joystick.h>

using namespace std;

//TODO(Logan)->Create a FileReader and possibly FileWriter classes. These
// classes should be platform independent.
class Program {
private:
	KeyMapping _keyMap;

	void loadKeyMap(string fileLoc);

protected:
	Joystick* p_joystick;

public:
	Program();
	virtual ~Program();
	static bool isRunning;
	KeyMapping* getKeyMap() { return &_keyMap; }
	void setKeyMap(KeyMapping map) { _keyMap = map; }
	virtual void sendKeyPress(KeyboardButton button) = 0;
	virtual void start() = 0;
	virtual Joystick* getJoystick() const { return p_joystick; }
};

#endif
