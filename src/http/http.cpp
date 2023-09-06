#include "webserv.hpp"

string error(u_int32_t code, const string& message);

const string http(const string& req){
	std::istringstream inputStream(req);
    std::string line;

	/*===-----						Init Line						   -----===*
	METHOD PATH+PARAMS PROTOCOL

	Method: GET | POST | PATCH | DELETE | ...
	Path + Params: /test | / | /hello/world?query=true
	Protocol: HTTP/1.1

	Ex:
	GET /test?query=true HTTP/1.1
	*/

	if (!std::getline(inputStream, line)){
		return error(400, "The Request is empty");
	}
	std::cout << "Init Line: " << line << std::endl;





	/*===-----						Host Header						   -----===*
	Host: HOSTNAME:PORT

	Hostname: localhost | awillems.42.fr
	Port (optional): 8000 | 4000 | ...

	Ex:
	Host: awillems.42.fr:4000
	*/

	string req_host;
	u_int32_t req_port;

	if (!std::getline(inputStream, line)){
		return error(400, "The host header is missing");
	}
	std::cout << "Host header Line: " << line << std::endl;





	/*===-----						Headers							   -----===*
	HEADER_KEY: HEADER_VALUE

	Ex:
	Accept-Language: en-US,en
	*/
	map<string, string> req_headers;
    while (std::getline(inputStream, line) && line != "\r") {
        std::cout << "Header Line: " << line << std::endl;
    }





	/*===-----						Body							  -----===*/







	return error(404, "This Page has not been Found");
}
