#include "Request.hpp"

//	GET / HTTP/1.1
//	Host: www.example.com
//	User-Agent: Mozilla/5.0
//	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
//	Accept-Language: en-GB,en;q=0.5
//	Accept-Encoding: gzip, deflate, br
//	Connection: keep-alive

void test_first_header();
void test_host_header();
void test_header();
void test_data();

int main(){
	test_first_header();
	test_host_header();
	test_header();
	test_data();
	return 0;
}
