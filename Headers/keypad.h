#ifndef KEYPAD_H
#define KEYPAD_H

using namespace std;

#include <unordered_map>

typedef unsigned long ControllerButton;
typedef unsigned long KeyboardButton;

struct KeyBind {
	ControllerButton source;
	KeyboardButton destination;
};

class Program {
private:
	unordered_map<ControllerButton, KeyboardButton> _bindings;

public:
	~Program();
	void addBinding(KeyBind);
	void removeBinding(KeyBind);
	void updateBinding(KeyBind);
	unordered_map<ControllerButton, KeyboardButton> getBindings() { return _bindings; }
};

#endif