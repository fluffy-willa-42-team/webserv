/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseLine.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:21:18 by awillems          #+#    #+#             */
/*   Updated: 2023/05/02 10:24:25 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestHeader.hpp"

void RequestHeader::parse_line(const std::string& line, size_t index){
	switch (index)
	{
		case 0:		return (parseStartLine(line));
		case 1:		return (parseHostHeader(line));
		default:	return (parseHeader(line));
	}
}

void RequestHeader::parseStartLine(const std::string& line){
	std::cout << line << std::endl;
}

void RequestHeader::parseHostHeader(const std::string& line){
	std::cout << line << std::endl;
}

void RequestHeader::parseHeader(const std::string& line){
	std::cout << line << std::endl;
}