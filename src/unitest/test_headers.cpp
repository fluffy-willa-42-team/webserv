/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_headers.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 08:50:55 by awillems          #+#    #+#             */
/*   Updated: 2023/05/03 12:10:58 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "test.hpp"

void test(const string& value, bool success_expected);

#define HEADER_TESTS_LENGTH 8
#define HEADER_TESTS {\
	{ true,		"abc: def\n"	},\
	{ true,		"abc: \n"		},\
	{ false,	"abc:\n"		},\
	{ false,	"abc:def\n"		},\
	{ false,	": def\n"		},\
	{ false,	"abcs\n"		},\
	{ true,	"\n"				},\
	{ true,		""				},\
}

#define CORRECT_HEADERS_TEST "GET / HTTP/1.1\n\
Host: www.example.com:420\n"

void test_header(){
	unitests unitests_headers[] = HEADER_TESTS;

	cout << "Test Non Mandatory Header" << endl;
	for (int i = 0; i < HEADER_TESTS_LENGTH; i++){
		test(string() + unitests_headers[i].value, false);
		test(string() + CORRECT_HEADERS_TEST + unitests_headers[i].value, unitests_headers[i].success_expected);
	}
}