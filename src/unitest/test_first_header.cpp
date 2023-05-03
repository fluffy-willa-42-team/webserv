/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_first_header.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 08:50:55 by awillems          #+#    #+#             */
/*   Updated: 2023/05/03 09:39:43 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "test.hpp"

void test(const string& value, bool success_expected);

#define HEADER_TESTS_LENGTH 22
#define HEADER_TESTS {\
	{ true,		"GET / HTTP/1.1\n"	},\
	{ false,	"GET/ HTTP/1.1\n"	},\
	{ false,	"GET /HTTP/1.1\n"	},\
	{ false,	"GET /\n"			},\
	{ false,	"GET / \n"			},\
	{ false,	"GET /abc\n"		},\
	{ false,	"GET /abc \n"		},\
	{ false,	"GET /abc.cpp\n"	},\
	{ false,	"GET /abc.cpp \n"	},\
	{ false,	"GET /abc \n"		},\
	{ false,	"GET /abc.cpp\n"	},\
	{ false,	"GET /abc.cpp \n"	},\
	{ true,		"POST / HTTP/1.1\n"	},\
	{ false,	"POST/ HTTP/1.1\n"	},\
	{ false,	"POST /HTTP/1.1\n"	},\
	{ false,	" / HTTP/1.1\n"		},\
	{ false,	"/ HTTP/1.1\n"		},\
	{ false,	" /HTTP/1.1\n"		},\
	{ false,	""					},\
	{ false,	"\n"				},\
	{ false,	"    \n"			},\
	{ false,	"xd\n"				},\
}

#define CORRECT_HEADERS_TEST "\
Host: www.example.com\n\
User-Agent: Mozilla/5.0\n\
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\n\
Accept-Language: en-GB,en;q=0.5\n\
Accept-Encoding: gzip, deflate, br\n\
Connection: keep-alive"

void test_first_header(){
	unitests unitests_headers[] = HEADER_TESTS;

	for (int i = 0; i < HEADER_TESTS_LENGTH; i++){
		test(string(unitests_headers[i].value), false);
		test(string(unitests_headers[i].value) + CORRECT_HEADERS_TEST, unitests_headers[i].success_expected);
	}
}