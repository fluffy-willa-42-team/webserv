#include "Request.hpp"
#include "test.hpp"

void test(const string& value, bool success_expected);

#define HEADER_TESTS_LENGTH 10
#define HEADER_TESTS {\
	{ true,		"Host: www.example.com\n"		},\
	{ true,		"Host: www.example.com:80\n"	},\
	{ false,	"Host: www.example.com:80000\n"	},\
	{ true,		"Host: www.example.com:0\n"		},\
	{ false,	"Host: www.example.com:\n"		},\
	{ false,	"Host: "						},\
	{ false,	": www.example.com\n"			},\
	{ false,	"\n"							},\
	{ false,	""								},\
	{ false,	"::"							},\
}

#define CORRECT_HEADERS_TEST "GET / HTTP/1.1\n"

void test_host_header(){
	unitests unitests_headers[] = HEADER_TESTS;

	cout << "Test Host Header" << endl;
	for (int i = 0; i < HEADER_TESTS_LENGTH; i++){
		test(string() + unitests_headers[i].value, false);
		test(string() + CORRECT_HEADERS_TEST + unitests_headers[i].value, unitests_headers[i].success_expected);
	}
}
