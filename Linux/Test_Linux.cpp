#include <cstdio>
#include <iostream>
#include <assert.h>
#include <linuxprogram.h>

using namespace std;

#define JOY_DEV "/dev/input/js0"

void assertKeymapSize(KeyMapping* keyMap, int expectedSize);
void display(LinuxJoystick*);

int main(int argc, char** argv) {
	LinuxProgram* p = new LinuxProgram();

	KeyBind keyMap = {};
	keyMap.source = 0;
	keyMap.destination = 1;

	p->getKeyMap()->addBinding(keyMap);
	p->getKeyMap()->addBinding(keyMap);

	KeyMapping* map = p->getKeyMap();

	assertKeymapSize(map, 1);
	assert(p->getKeyMap()->getKeyboardButtonFor(keyMap.source) == keyMap.destination);

	LinuxJoystick* js = p->getJoystick();
	display(js);

	while (true) {
		js->fillState();

		if (!js->isActive()) {
			cout << "State:  NOT ACTIVE" << endl;
			break;
		}
	}

	delete p;
}

void display(LinuxJoystick* js) {
	cout << "Name: " << js->getName() << endl;
	cout << "Status: " << js->isActive() << endl;
	cout << "Button Count: " << js->getButtonCount() << endl;
	cout << "Axis Count: " << js->getAxisCount() << endl;
}

void assertKeymapSize(KeyMapping* keyMap, int expectedSize) {
	assert(keyMap->size() == expectedSize);
}