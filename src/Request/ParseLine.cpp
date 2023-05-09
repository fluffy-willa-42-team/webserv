#include "Request.hpp"
#include <iostream>

// {FIRST}: {SECOND}
bool parseSingleLine(pair<string, string>& res, const string& line, const string& sep){
	size_t i = line.find_first_of(sep);
	if (i == string::npos || i + sep.length() > line.length())
		return false;
	res.first = line.substr(0, i);
	res.second = line.substr(i + sep.length());
	return true;
}

bool Request::parse_line(const string& line, size_t index){
	switch (index)
	{
		case 0:		return (parseStartLine(line));
		case 1:		return (parseHostHeader(line));
		default:	return (parseHeader(line));
	}
}

bool Request::parseStartLine(const string& line){
	size_t i = line.find(' ');
	if (i == string::npos || i < 1)
		throw InvalidRequest("Invalid Host Header");
	
	method = line.substr(0, i);
	string rest = line.substr(i + 1);
	
	i = rest.find(' ');
	if (i == string::npos || rest.length() - i - 1 < 1)
		throw InvalidRequest("Invalid Host Header");
	
	path = rest.substr(0, i);
	protocol = rest.substr(i + 1);
	return true;
}

bool Request::parseHostHeader(const string& line){
	pair<string, string> data;
	if (!parseSingleLine(data, line, ": ")
		|| data.first != "Host"
		|| data.second.length() < 1)
		throw InvalidRequest("Invalid Header");
	if (parseSingleLine(data, data.second, ":")){
		host = data.first;
		if (data.second.length() < 1)
			throw InvalidRequest("Missing Port");
		std::istringstream(data.second) >> port;
		if (port > 65535)
			throw InvalidRequest("Port Invalid");
	}
	else {
		host = data.second;
	}
	return true;
}

bool Request::parseHeader(const string& line){
	pair<string, string> data;
	if (!parseSingleLine(data, line, ": ")
		|| data.first.length() < 1)
		throw InvalidRequest("Wrong Header Key");
	headers[data.first] = data.second;
	return true;
}