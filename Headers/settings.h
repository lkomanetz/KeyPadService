#ifndef SETTINGS_H
#define SETTINGS_H

#include <map>
#include <iostream>
#include <fstream>
#include <string>

class Settings {
private:
	std::string _delimiter;
	const char* _fileName;
	std::map<std::string, std::string> _settingsMap;

public:
	Settings();
	void load();
	std::string getValue(std::string settingName) const;

};

#endif