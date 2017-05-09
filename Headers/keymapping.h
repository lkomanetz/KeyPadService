#ifndef KEYMAPPING_H
#define KEYMAPPING_H

#include <unordered_map>

using namespace std;

typedef unsigned short ControllerButton;
typedef unsigned long KeyboardButton;

const KeyboardButton NO_BUTTON = 500;

struct KeyBind {
	ControllerButton source;
	KeyboardButton destination;
};

class KeyMapping {
private:
	unordered_map<ControllerButton, KeyboardButton> _bindings;

public:
	~KeyMapping();
	void addBinding(KeyBind);
	void removeBinding(KeyBind);
	void updateBinding(KeyBind);
	int length() { return _bindings.size(); }
	KeyboardButton* getKeyboardButtonFor(ControllerButton); 
};

#endif
