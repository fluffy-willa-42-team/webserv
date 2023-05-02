#include <iostream>
#include "Request.hpp"

//	GET / HTTP/1.1
//	Host: www.example.com
//	User-Agent: Mozilla/5.0
//	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
//	Accept-Language: en-GB,en;q=0.5
//	Accept-Encoding: gzip, deflate, br
//	Connection: keep-alive


int main(){
	char test[245] = "GET / HTTP/1.1\nHost: www.example.com\nUser-Agent: Mozilla/5.0\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\nAccept-Language: en-GB,en;q=0.5\nAccept-Encoding: gzip, deflate, br\nConnection: keep-alive";

	Request header(test);
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