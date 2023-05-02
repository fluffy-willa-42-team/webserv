/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHeader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:11:00 by awillems          #+#    #+#             */
/*   Updated: 2023/05/02 12:32:18 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestHeader.hpp"

RequestHeader::RequestHeader(const string& input)
	: port(80)
{
	try
	{
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
	catch(const InvalidRequest& e)
	{
		std::cerr << e.what() << '\n';
	}
}
