#include "webserv.hpp"
#include "utils.hpp"
#include "request_validation.hpp"

string error(u_int32_t code, const string& message);

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
	removeCarriageReturn(line);

	vector<string> initline = split(line, " ");
	if (initline.size() != 3){
		return error(400, "Init line is invalid");
	}


	// Method
	string req_method = initline[0];
	{
		cout << "Method: " << req_method << endl;
		e_validation_status validation_status = is_method_valid(req_method);
		if (validation_status == NOT_ALLOWED){
			return error(405, "");
		}
		else if (validation_status == BAD_REQUEST){
			return error(400, "Method is invalid");
		}
	}

	// Path + Param
	string req_path_param = initline[1];
	{
		cout << "Path + Param: " << req_path_param << endl;
		if (!is_path_valid(req_path_param)){
			return error(400, "Path is invalid");
		}
	}

	// Protocol
	{
		string req_protocol = initline[2];
		cout << "Protocol: " << req_protocol << endl;
		e_validation_status validation_status = is_method_valid(req_method);
		if (validation_status == NOT_ALLOWED){
				return error(505, "");
		}
		else if (validation_status == BAD_REQUEST){
			return error(400, "Protocol is invalid");

		}
	}





	/*===-----						Headers							   -----===*
	HEADER_KEY: HEADER_VALUE

	Ex:
	Accept-Language: en-US,en
	*/
	map<string, string> req_headers;
    while (getline(ss_line_by_line, line) && line != "\r") {
		removeCarriageReturn(line);
		vector<string> headerline = splitFirst(line, ": ");
		if (headerline.size() != 2){
			return error(400, "Headers are invalid");
		}
        req_headers[headerline[0]] = headerline[1];
    }





	/*===-----						Host Header						   -----===*
	Host: HOSTNAME:PORT

	Hostname: localhost | awillems.42.fr
	Port (optional): 8000 | 4000 | ...

	// WARNING Host header is not necassarly the first header !!!

	Ex:
	Host: awillems.42.fr:4000
	*/

	// string req_host;
	// u_int32_t req_port;

	// if (!getline(ss_line_by_line, line)){
	// 	return error(400, "The host header is missing");
	// }
	// cout << "Host header Line: " << line << endl;






	/*===-----						Body							  -----===*/




	for (map<string, string>::iterator it = req_headers.begin(); it != req_headers.end(); it++){
		cout << it->first << ": \"" << it->second << "\"" << endl;
	}


	return error(404, "This Page has not been Found");
}
