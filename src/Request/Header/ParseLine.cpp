/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseLine.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:21:18 by awillems          #+#    #+#             */
/*   Updated: 2023/05/02 10:54:32 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestHeader.hpp"

// {FIRST}: {SECOND}
pair<string, string> parseSingleLine(const string& line){
	size_t i = 0;
	while (i < line.length() && line[i] != ':'){
		i++;
	}
	return pair<string, string>(line.substr(0, i), line.substr(i + 2));
}

void RequestHeader::parse_line(const string& line, size_t index){
	switch (index)
	{
		case 0:		return (parseStartLine(line));
		case 1:		return (parseHostHeader(line));
		default:	return (parseHeader(line));
	}
}

void RequestHeader::parseStartLine(const string& line){
	std::cout << line << std::endl;
}

void RequestHeader::parseHostHeader(const string& line){
	cout << line << endl;
	parseSingleLine(line);
}

void RequestHeader::parseHeader(const string& line){
	cout << line << endl;
	parseSingleLine(line);
}