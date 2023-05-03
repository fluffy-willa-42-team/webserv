/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseLine.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:21:18 by awillems          #+#    #+#             */
/*   Updated: 2023/05/03 12:06:05 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestHeader.hpp"
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

bool RequestHeader::parse_line(const string& line, size_t index){
	switch (index)
	{
		case 0:		return (parseStartLine(line));
		case 1:		return (parseHostHeader(line));
		default:	return (parseHeader(line));
	}
}

bool RequestHeader::parseStartLine(const string& line){
	size_t i = line.find(' ');
	if (i == string::npos || i < 1)
		throw InvalidRequest("Invalid Host Header");
	
	this->method = line.substr(0, i);
	string rest = line.substr(i + 1);
	
	i = rest.find(' ');
	if (i == string::npos || rest.length() - i - 1 < 1)
		throw InvalidRequest("Invalid Host Header");
	
	this->path = rest.substr(0, i);
	this->protocol = rest.substr(i + 1);
	return true;
}

bool RequestHeader::parseHostHeader(const string& line){
	pair<string, string> data;
	if (!parseSingleLine(data, line, ": ")
		|| data.first != "Host"
		|| data.second.length() < 1)
		throw InvalidRequest("Invalid Header");
	if (parseSingleLine(data, data.second, ":")){
		this->host = data.first;
		if (data.second.length() < 1)
			throw InvalidRequest("Missing Port");
		std::istringstream(data.second) >> this->port;
		if (this->port > 65535)
			throw InvalidRequest("Port Invalid");
	}
	else {
		this->host = data.second;
	}
	return true;
}

bool RequestHeader::parseHeader(const string& line){
	pair<string, string> data;
	if (!parseSingleLine(data, line, ": ")
		|| data.first.length() < 1)
		throw InvalidRequest("Wrong Header Key");
	this->non_mandatory[data.first] = data.second;
	return true;
}