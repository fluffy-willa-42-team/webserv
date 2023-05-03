/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHeader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:11:00 by awillems          #+#    #+#             */
/*   Updated: 2023/05/03 07:21:53 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestHeader.hpp"

RequestHeader::RequestHeader(const string& input)
	: port(80)
{
	cout << "\e[0;36m" << input << "\e[0m" << endl;
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
	cout << endl;
}
