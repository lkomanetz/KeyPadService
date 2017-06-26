#include <settings.h>

Settings::Settings() {
	_fileName = "settings.txt";
	_delimiter = "=";
}

void Settings::load() {
	std::ifstream inFile(_fileName);
	if (!inFile) {
		throw "Unable to load settings...";
	}

	std::string lineOfText;
	while (std::getline(inFile, lineOfText)) {
		int startingIndex = lineOfText.find(_delimiter);
		_keybindingsLocation = lineOfText.substr(++startingIndex, lineOfText.size());
	}
}