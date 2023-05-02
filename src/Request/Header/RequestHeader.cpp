/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHeader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:11:00 by awillems          #+#    #+#             */
/*   Updated: 2023/05/02 11:43:24 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestHeader.hpp"

RequestHeader::RequestHeader(const string& input){
	std::stringstream test(input);
	string line;

	size_t i = 0;
	while (std::getline(test, line))
	{
		parse_line(line, i);
		line.clear();
		i++;
	}
}

RequestHeader::RequestHeader(const RequestHeader& other){
	(void) other; // TODO
}
		
const RequestHeader& RequestHeader::operator=(const RequestHeader& other){
	(void) other; // TODO
	return (*this);
}
