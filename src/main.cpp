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

#define HEADER_TESTS_LENGTH 18
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
}

#define CORRECT_HEADERS_TEST "\
Host: www.example.com:\n\
User-Agent: Mozilla/5.0\n\
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\n\
Accept-Language: en-GB,en;q=0.5\n\
Accept-Encoding: gzip, deflate, br\n\
Connection: keep-alive"


int main(){
	unitests unitests_headers[] = HEADER_TESTS;

	for (int i = 0; i < HEADER_TESTS_LENGTH; i++){
		string value = string() + unitests_headers[i].value + CORRECT_HEADERS_TEST;

		if (VERBOSE_TEST)
			cout << "\e[0;36m" << value << "\e[0m" << endl;

		Request header(value);
		if (header.isValid() == unitests_headers[i].success_expected){
			cout << "\e[0;32m" << "Success !" << "\e[0m" << endl;
		}
		else {
			cout << "\e[0;31m" << "Failure !" << "\e[0m" << endl;
		}
		if (VERBOSE_TEST)
			cout << endl;
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