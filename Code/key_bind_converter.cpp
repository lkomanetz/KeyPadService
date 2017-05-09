#include <keybindconverter.h>

KeyBind KeyBindConverter::toKeyBind(string text) {
	stringstream ss;
	int index = text.find("=");
	KeyBind bind = {};

	string first = text.substr(0, index);
	string last = text.substr(index + 1, text.length());

	if (last.compare("NULL") == 0) {
		bind.source = NO_BUTTON;
		bind.destination = NO_BUTTON;
	}
	else {
		KeyboardButton btn;
		ss << hex << last;
		ss >> btn;

		bind.source = stoi(first);
		bind.destination = btn;
	}

	return bind;
}