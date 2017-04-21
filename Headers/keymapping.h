#ifndef KEYMAPPING_H
#define KEYMAPPING_H

#include <unordered_map>
//TODO(Logan) -> Fix this issue where the ControllerButton and KeyboardButton typedefs aren't working.
#include <keypad.h>

using namespace std;

class KeyMapping {
private:
	unordered_map<ControllerButton, KeyboardButton> _bindings;

public:
	void addBinding(KeyBind);
	void removeBinding(KeyBind);
	void updateBinding(KeyBind);
	KeyboardButton getKeyboardButtonFor(ControllerButton);
};

#endif