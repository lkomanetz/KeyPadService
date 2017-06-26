#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <fstream>
#include <string>

class Settings {
private:
	std::string _delimiter;
	const char* _fileName;
	std::string _keybindingsLocation;

public:
	Settings();
	void load();
	std::string getKeybindingsLocation() { return _keybindingsLocation; }

};

#endif