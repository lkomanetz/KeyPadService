#include <keymapping.h>
#include <iostream>

using namespace std;

KeyMapping::~KeyMapping() {
	_bindings.clear();
}

void KeyMapping::addBinding(KeyBind binding) {
	_bindings.insert({ binding.source, binding.destination });
}

void KeyMapping::removeBinding(KeyBind binding) {
	_bindings.erase(binding.source);
}

void KeyMapping::updateBinding(KeyBind binding) {
	_bindings[binding.source] = binding.destination;
}

KeyboardButton* KeyMapping::getKeyboardButtonFor(ControllerButton button) {
	return &_bindings[button];
}