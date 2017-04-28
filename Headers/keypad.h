#ifndef KEYPAD_H
#define KEYPAD_H

#include <keymapping.h>
#include <joystick.h>

using namespace std;

class Program {
private:
	KeyMapping _keyMap;

protected:
	Joystick* p_joystick;

public:
	Program();
	virtual ~Program();
	static bool isRunning;
	KeyMapping* getKeyMap() { return &_keyMap; }
	virtual Joystick* getJoystick() const { return p_joystick; }
};

#endif
