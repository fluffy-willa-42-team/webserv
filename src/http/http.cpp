#include "webserv.hpp"

string error(u_int32_t code, const string& message);

bool is_method_valid(const string& method);

const string http(const string& req){
	stringstream ss_line_by_line(req);
    string line;

	/*===-----						Init Line						   -----===*
	METHOD PATH+PARAMS PROTOCOL

	Method: GET | POST | PATCH | DELETE | ...
	Path + Params: /test | / | /hello/world?query=true
	Protocol: HTTP/1.1

	Ex:
	GET /test?query=true HTTP/1.1
	*/

	if (!getline(ss_line_by_line, line)){
		return error(400, "The Request is empty");
	}
	stringstream ss_init_line(line);
    string token;

	// Method
	string req_method;
	ss_init_line >> req_method;
	cout << "Method: " << req_method << endl;
	if (!is_method_valid(req_method)){
		return error(405, "Method Not Allowed or Unrecognized");
	}

	// Path + Param
	string req_path_param;
	ss_init_line >> req_path_param;
	cout << "Path + Param: " << req_path_param << endl;

	// Protocol
	string protocol;
	ss_init_line >> protocol;
	cout << "Protocol: " << protocol << endl;




	/*===-----						Host Header						   -----===*
	Host: HOSTNAME:PORT

	Hostname: localhost | awillems.42.fr
	Port (optional): 8000 | 4000 | ...

	Ex:
	Host: awillems.42.fr:4000
	*/

	string req_host;
	u_int32_t req_port;

	if (!getline(ss_line_by_line, line)){
		return error(400, "The host header is missing");
	}
	// cout << "Host header Line: " << line << endl;





	/*===-----						Headers							   -----===*
	HEADER_KEY: HEADER_VALUE

	Ex:
	Accept-Language: en-US,en
	*/
	map<string, string> req_headers;
    while (getline(ss_line_by_line, line) && line != "\r") {
        // cout << "Header Line: " << line << endl;
    }





	/*===-----						Body							  -----===*/







	return error(404, "This Page has not been Found");
}
