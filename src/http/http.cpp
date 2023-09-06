#include "webserv.hpp"

#define response_example "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 112\n\n<html>\n<head>\n	<title>200 OK</title>\n	</head>\n	<body>\n		<h1>OK</h1>\n		<p>The request was successful.</p>\n	</body>\n</html>"

string error(u_int32_t code, const string& message);

const string http(const string& req){
	std::istringstream inputStream(req);
    std::string line;

	/*===-----		Init Line		-----===*/
	if (!std::getline(inputStream, line)){
		return error(400, "The Request is empty");
	}
	std::cout << "Init Line: " << line << std::endl;



	/*===-----		Host Header		-----===*/
	map<string, string> req_headers;
	if (!std::getline(inputStream, line)){
		return error(400, "The host header is missing");
	}
	std::cout << "Host header Line: " << line << std::endl;



	/*===-----		Headers			-----===*/
	
    while (std::getline(inputStream, line) && line != "\r") {
        std::cout << "Header Line: " << line << std::endl;
    }



	return error(404, "This Page has not been Found");
}






/*

GET / HTTP/1.1
Host: localhost:8001
Connection: keep-alive
Cache-Control: max-age=0
sec-ch-ua: "Brave";v="107", "Chromium";v="107", "Not=A?Brand";v="24"
sec-ch-ua-mobile: ?0
sec-ch-ua-platform: "macOS"
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/107.0.0.0 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,;q=0.8
Sec-GPC: 1
Accept-Language: en-US,en
Sec-Fetch-Site: none
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Accept-Encoding: gzip, deflate, br

*/