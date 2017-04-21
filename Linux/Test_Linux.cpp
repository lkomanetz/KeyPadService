#include <cstdio>
#include <iostream>
#include <assert.h>
#include <linuxprogram.h>
#include <joystick.h>

using namespace std;

void printBindings(unordered_map<ControllerButton, KeyboardButton>);

int main(int argc, char** argv) {
	LinuxProgram* p = new LinuxProgram();

	KeyBind keyMap = {};
	keyMap.source = 0;
	keyMap.destination = 1;

	p->addBinding(keyMap);
	p->addBinding(keyMap);

	auto bindings = p->getBindings();
	printBindings(bindings);

	assert(bindings.size() == 1);
	assert(bindings.begin()->first == keyMap.source);

	delete p;

	Joystick js;
	cout << "Name: " << js.getName() << endl;
	cout << "Button Count: " << js.getButtonCount() << endl;
	cout << "Axis Count: " << js.getAxisCount() << endl;
}

void printBindings(unordered_map<ControllerButton, KeyboardButton> bindings) {
	for (auto element : bindings) {
		std::cout << element.first << "::" << element.second << std::endl;
	}
}