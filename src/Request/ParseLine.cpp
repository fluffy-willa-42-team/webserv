#include "Request.hpp"
#include <iostream>

bool has_input(const string& line, const string& input);
bool parseSingleLine(pair<string, string>& res, const string& line, const string& sep);

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
	if (i == string::npos || i < 1){
		throw InvalidRequest("Invalid Host Header1");
	}
	
	method = line.substr(0, i);
	string rest = line.substr(i + 1);
	
	i = rest.find(' ');
	if (i == string::npos || rest.length() - i - 1 < 1){
		throw InvalidRequest("Invalid Host Header2");
	}
	
	path = rest.substr(0, i);
	protocol = rest.substr(i + 1);
	if (protocol != PROTOCOL){
		cout << line << " " << protocol << " " << PROTOCOL << endl;
		throw InvalidRequest("Invalid Host Header3");
	}
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
		stringstream(data.second) >> port;
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
		|| has_input(data.first, ":")
		|| data.first.length() < 1)
		throw InvalidRequest("Wrong Header Key");
	headers[data.first] = data.second;
	return true;
}