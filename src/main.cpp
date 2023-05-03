#include <iostream>
#include "Request.hpp"

//	GET / HTTP/1.1
//	Host: www.example.com
//	User-Agent: Mozilla/5.0
//	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
//	Accept-Language: en-GB,en;q=0.5
//	Accept-Encoding: gzip, deflate, br
//	Connection: keep-alive

typedef struct unitests {
    int			success_expected;
    const char* value;
}	unitests;

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
Host: www.example.com:\n\
User-Agent: Mozilla/5.0\n\
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\n\
Accept-Language: en-GB,en;q=0.5\n\
Accept-Encoding: gzip, deflate, br\n\
Connection: keep-alive"

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

int main(){
	unitests unitests_headers[] = HEADER_TESTS;

	for (int i = 0; i < HEADER_TESTS_LENGTH; i++){
		test(string("") + unitests_headers[i].value, false);
		test(string("") + unitests_headers[i].value + CORRECT_HEADERS_TEST, unitests_headers[i].success_expected);
	}
	return 0;
}


/*
class structure


request : {
	get
	post
	delete
}

response

*/