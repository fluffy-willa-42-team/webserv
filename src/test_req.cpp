#include "Request.hpp"
#include "Response.hpp"
#include "Config.hpp"

#define TEST_GET "GET / HTTP/1.1\nHost: localhost:8001\nConnection: keep-alive\nCache-Control: max-age=0\nsec-ch-ua: \"Chromium\";v=\"110\", \"Not A(Brand\";v=\"24\", \"Google Chrome\";v=\"110\"\nsec-ch-ua-mobile: ?0\nsec-ch-ua-platform: \"macOS\"\nUpgrade-Insecure-Requests: 1\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7\nSec-Fetch-Site: none\nSec-Fetch-Mode: navigate\nSec-Fetch-User: ?1\nSec-Fetch-Dest: document\nAccept-Encoding: gzip, deflate, br\nAccept-Language: fr,en-US;q=0.9,en;q=0.8,fr-FR;q=0.7"
#define TEST_GET2 "GET / HTTP/1.1\nHost: www.example.com\nUser-Agent: curl/7.68.0\nAccept: */*"


void test_req(){
	Config config("test1");
	Request req(TEST_GET2);

	cout << req << endl;

	Response* res = response_factory(req, config);
	
	if (!res)
		throw runtime_error("No Response");
	cout << *res << endl;
}
