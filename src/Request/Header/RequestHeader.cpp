/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHeader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:11:00 by awillems          #+#    #+#             */
/*   Updated: 2023/05/03 12:04:40 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestHeader.hpp"

RequestHeader::RequestHeader(const string& input)
	: valid(false), port(80)
{
	try
	{
		std::stringstream test(input);
		string line;

		if (input.length() < 1)
			return ;

		size_t i = 0;
		while (std::getline(test, line) && line != "\n")
		{
			parse_line(line, i);
			line.clear();
			i++;
		}
		if (i < 2){
			throw InvalidRequest("Missing Content");
		}
		this->valid = true;
	}
	catch(const InvalidRequest& e){
		cout << e.what() << endl;
	}
}
