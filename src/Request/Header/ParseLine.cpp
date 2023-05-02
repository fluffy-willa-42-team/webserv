/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseLine.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:21:18 by awillems          #+#    #+#             */
/*   Updated: 2023/05/02 12:30:51 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestHeader.hpp"
#include <iostream>

// {FIRST}: {SECOND}
bool parseSingleLine(pair<string, string>& res, const string& line){
	size_t i = 0;
	while (i < line.length() && line[i] != ':'){
		i++;
	}
	if (i == line.length())
		return false;
	res.first = line.substr(0, i);
	res.second = line.substr(i + 2);
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
	size_t i = 0;
	while (i < line.length() && line[i] != ' '){
		i++;
	}
	if (i >= line.length())
		return false;
	this->method = line.substr(0, i);
	
	string rest = line.substr(i + 1);
	i = 0;
	while (i < rest.length() && rest[i] != ' '){
		i++;
	}
	if (i >= rest.length())
		return false;
	this->path = rest.substr(0, i);
	if (rest.length() - i < 1)
		return false;
	this->protocol = rest.substr(i + 1);

	cout << this->protocol << " | " << this->method << " | " << this->path << endl;
	return true;
}

bool RequestHeader::parseHostHeader(const string& line){
	pair<string, string> data;
	if (!parseSingleLine(data, line) || data.first != "Host")
		throw InvalidRequest();
	if (parseSingleLine(data, data.second)){
		this->host = data.first;
		// this->port = (size_t) data.second;
	}
	else {
		this->host = data.second;
	}
	return true;
}

bool RequestHeader::parseHeader(const string& line){
	pair<string, string> data;
	bool status = parseSingleLine(data, line);
	if (!status){
		cout << "error" << endl;
		return false;
	}
	cout << data.first << "\t= " << data.second << endl;
	return true;
}