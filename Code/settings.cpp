#include <settings.h>

Settings::Settings() {
	_fileName = "settings.txt";
	_delimiter = "=";
}

void Settings::load() {
	std::ifstream inFile(_fileName);
	if (!inFile) {
		throw std::runtime_error("Unable to load settings...");
	}

	std::string lineOfText;
	while (std::getline(inFile, lineOfText)) {
		int startingIndex = lineOfText.find(_delimiter);
		std::string settingName = lineOfText.substr(0, startingIndex);
		std::string settingValue = lineOfText.substr(++startingIndex, lineOfText.size());
		_settingsMap.insert(std::pair<std::string, std::string>(settingName, settingValue));
	}
}

std::string Settings::getValue(std::string settingName) {
	auto search = _settingsMap.find(settingName);
	if (search == _settingsMap.end()) {
		std::string msg = "Setting '" + settingName + "' not found.";
		throw std::runtime_error(msg.c_str());
	}

	return search->second;
}