#ifndef KEYPAD_H
#define KEYPAD_H

#include <keymapping.h>
#include <joystick.h>

using namespace std;

class Program {
private:
	KeyMapping _keyMap;

protected:
	Joystick* _joystick;

public:
	~Program();
	KeyMapping* getKeyMap() { return &_keyMap; }
	virtual Joystick* getJoystick() const { return _joystick; }
};

#endif
