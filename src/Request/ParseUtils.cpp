#include "Request.hpp"
#include <iostream>

// {FIRST}: {SECOND}
bool parseSingleLine(pair<string, string>& res, const string& line, const string& sep){
	size_t i = line.find(sep);
	if (i == string::npos || i + sep.length() > line.length())
		return false;
	res.first = line.substr(0, i);
	res.second = line.substr(i + sep.length());
	return true;
}

bool has_input(const string& line, const string& input)
{
	return (line.find(input) != string::npos);
}