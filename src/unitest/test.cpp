/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 08:47:48 by awillems          #+#    #+#             */
/*   Updated: 2023/05/03 10:44:55 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "test.hpp"

bool can_print(Request& header, bool success_expected){
	return (VERBOSE_TEST
	&& (
		(HIDE_SUCCESFULL_TEST && !(header.isValid() == success_expected))
		|| !HIDE_SUCCESFULL_TEST
	));
}

void test(const string& value, bool success_expected)
{
		
	Request header(value);

	if (can_print(header, success_expected)){
		cout << "\e[0;36m\"" << value << "\"\e[0m" << endl;
		cout << "Res: " << header << endl;
		cout << "Expected: " << (success_expected ? "true" : "false") << endl;
		cout << "Result:   " << (header.isValid() ? "true" : "false") << endl;
	}

	if (header.isValid() == success_expected){
		cout << "\e[0;32m" << "Success !" << "\e[0m" << endl;
	}
	else {
		cout << "\e[0;31m" << "Failure !" << "\e[0m" << endl;
	}

	if (can_print(header, success_expected))
		cout << endl << endl << endl;
	else if (VERBOSE_TEST)
		cout << endl;
}
