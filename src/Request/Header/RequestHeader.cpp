/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHeader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:11:00 by awillems          #+#    #+#             */
/*   Updated: 2023/05/03 08:18:22 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestHeader.hpp"

RequestHeader::RequestHeader(const string& input)
	: valid(false), port(80)
{
	if (VERBOSE_TEST)
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
		this->valid = true;
	}
	catch(const InvalidRequest& e)
	{
		if (VERBOSE_TEST)
			std::cerr << e.what() << '\n';
	}
}
