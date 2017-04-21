#include <../Headers/keypad.h>

Program::~Program() {
	_bindings.clear();
}

void Program::addBinding(KeyBind binding) {
	_bindings.insert({binding.source, binding.destination});
}

void Program::removeBinding(KeyBind binding) {
	_bindings.erase(binding.source);
}

void Program::updateBinding(KeyBind binding) {
	_bindings[binding.source] = binding.destination;
}