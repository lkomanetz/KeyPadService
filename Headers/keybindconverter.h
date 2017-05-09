#ifndef KEYBINDCONVERTER_H
#define KEYBINDCONVERTER_H

#include <keymapping.h>
#include <string>
#include <sstream>

class KeyBindConverter {
public:
	static KeyBind toKeyBind(string text);

};

#endif