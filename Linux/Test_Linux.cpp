#include <cstdio>
#include <iostream>
#include <assert.h>
#include <linuxprogram.h>

using namespace std;

void assertKeymapSize(KeyMapping* keyMap, int expectedSize);
KeyMapping buildMap();

int main(int argc, char** argv) {
	LinuxProgram* p = new LinuxProgram();
	KeyMapping keyMap = buildMap();

	p->setKeyMap(keyMap);
	KeyMapping* map = p->getKeyMap();

	assertKeymapSize(map, 4);
	assert(p->getKeyMap()->getKeyboardButtonFor(ControllerButtons::A_BUTTON) == 90);

	LinuxJoystick* js = p->getJoystick();

	while (true) {
		usleep(1000);

		if (!js->isActive()) {
			cout << "State:  NOT ACTIVE" << endl;
			break;
		}
	}

	delete p;
	usleep(1000);
	return 0;
}

KeyMapping buildMap() {
	KeyMapping map;
	for (int i = 0; i < 4; ++i) {
		KeyBind bind;
		bind.source = i;
		switch (i) {
			case 0:
				bind.destination = 90; // Z Key
				break;
			case 1:
				bind.destination = 88; // X Key
				break;
			case 2:
				bind.destination = 32; // Space bar
				break;
			case 3:
				bind.destination = 13; // Enter
				break;
		}

		map.addBinding(bind);
	}
	return map;
}

void assertKeymapSize(KeyMapping* keyMap, int expectedSize) {
	assert(keyMap->size() == expectedSize);
}