#ifndef INPUTPARAMETERPARSER_H
#define INPUTPARAMETERPARSER_H

using namespace std;

class InputParameterParser
{
private:
    vector<string> _tokens;

public:
    InputParameterParser(int& argc, char** argv);
    bool cmdOptionExists(const string& option) const;
    const string& getCmdOption(const string& option) const;
}

#endif