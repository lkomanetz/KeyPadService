#include <inputparameterparser.h>

InputParameterParser::InputParameterParser(int& argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        this->_tokens.push_back(string(argv[i]));
    }
}

const string& InputParameterParser::getCmdOption(const string& option) const {
    vector<string>::const_iterator iterator;
    iterator = find(this->tokens.begin(), this->tokens.end(), option);
    if (iterator != this->_tokens.end() && ++iterator != this->_tokens.end()) {
        return *iterator;
    }

    static const string empty_string("");
    return empty_string;
}

bool InputParameterParser::cmdOptionExists(const string& option) const {
    return find(this->_tokens.begin(), this-_tokens.end(), option) != this->_tokens.end();
}
