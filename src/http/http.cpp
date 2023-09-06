#include "webserv.hpp"

string error(u_int32_t code, const string& message);

const string http(const string& req){
	stringstream inputStream(req);
    string line;

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
	cout << "Init Line: " << line << endl;
	stringstream iss(line);
    string token;

	// Method
	iss >> token;
	cout << "Init Line: " << line << endl;

	// Path + Param
	iss >> token;

	// Protocol
	iss >> token;




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
	cout << "Host header Line: " << line << endl;





	/*===-----						Headers							   -----===*
	HEADER_KEY: HEADER_VALUE

	Ex:
	Accept-Language: en-US,en
	*/
	map<string, string> req_headers;
    while (std::getline(inputStream, line) && line != "\r") {
        cout << "Header Line: " << line << endl;
    }





	/*===-----						Body							  -----===*/







	return error(404, "This Page has not been Found");
}
