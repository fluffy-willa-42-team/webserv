/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 08:47:48 by awillems          #+#    #+#             */
/*   Updated: 2023/05/03 08:54:33 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

void test(const string& value, bool success_expected)
{
	if (VERBOSE_TEST)
		cout << "\e[0;36m" << value << "\e[0m" << endl;

	Request header(value);

	if (VERBOSE_TEST){
		cout << "Expected: " << (success_expected ? "true" : "false") << endl;
		cout << "Result:   " << (header.isValid() ? "true" : "false") << endl;
	}

	if (header.isValid() == success_expected){
		cout << "\e[0;32m" << "Success !" << "\e[0m" << endl;
	}
	else {
		cout << "\e[0;31m" << "Failure !" << "\e[0m" << endl;
	}

	if (VERBOSE_TEST)
		cout << endl;
}
