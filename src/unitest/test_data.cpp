/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_data.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 08:50:55 by awillems          #+#    #+#             */
/*   Updated: 2023/05/03 11:47:24 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "test.hpp"

void test(const string& value, bool success_expected);

#define DATA_TEST "POST /example.php HTTP/1.1\n\
Host: www.example.com\n\
Content-Type: application/x-www-form-urlencoded\n\
Content-Length: 25\n\
\n\
"

#define DATA_TESTS_LENGTH 4
#define DATA_TESTS {\
	{ true,		"name=John+Doe&age=30\n"	},\
	{ true,		"name=John+Doe&age=30"		},\
	{ true,		"\n"						},\
	{ true,		""							},\
}

#define CORRECT_HEADERS_TEST "GET / HTTP/1.1\n"

void test_data(){
	unitests unitests_headers[] = DATA_TESTS;

	cout << "Test First Header" << endl;
	for (int i = 0; i < DATA_TESTS_LENGTH; i++){
		test(string(DATA_TEST) + unitests_headers[i].value, unitests_headers[i].success_expected);
	}
}
