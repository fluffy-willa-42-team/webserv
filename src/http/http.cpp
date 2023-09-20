#include "http.hpp"

const string http(const string& req, Listener& listener, const Config& config){
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
			return error(405);
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
				return error(505); // HTTP Version not allowed
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
	Headers req_headers;
    while (getline(ss_line_by_line, line) && removeCarriageReturn(line) && line.length() > 0) {
		vector<string> headerline = splitFirst(line, ": ");
		if (is_header_valid(headerline) == BAD_REQUEST){
			return error(400, "Headers are invalid");
		}
        req_headers[headerline[0]] = headerline[1];
    }

	for (Headers::iterator it = req_headers.begin(); it != req_headers.end(); it++){
		cout << it->first << ": \"" << it->second << "\"" << endl;
	}





	/*===-----						Host Header						   -----===*
	Host: HOSTNAME:PORT

	Hostname: localhost | awillems.42.fr
	Port (optional): 8000 | 4000 | ...

	// WARNING Host header is not necassarly the first header !!!

	Ex:
	Host: awillems.42.fr:4000
	*/
	{
		if (!map_has_key(req_headers, string(HEADER_HOST))){
			return error(400, "Missing host header");
		}
	}

	


	/*===-----						Body							  -----===*/
	string req_body;
	{
		stringstream remainingContentStream;
		remainingContentStream << ss_line_by_line.rdbuf();
		req_body = remainingContentStream.str();
		if (req_body.length() != 0){
			if (!map_has_key(req_headers, string(HEADER_CONTENT_LENGTH))){
				return error(411, "Missing \"Content-Length\" header"); // TODO verify it is not code 412
			}
			else {
				u_int32_t content_length = stringToNumber(req_headers[HEADER_CONTENT_LENGTH]);
				while (req_body.length() < content_length){
					string buf;
					try {
						buf = listener.read_buff();
					}
					catch(const exception& e) {
						return error(411, "Invalid \"Content-Length\" header");
					}
					req_body += buf;
				}
				cout << YELLOW << req_body << RESET << endl;
			}
		}
	}





	/*===-----						XXXX							  -----===*/

	/*
	now that the request is parsed we now have to parse to config of all server
	to find the one that is valid and that worked an execute that.
	*/

	try {
		find_server(config, req_headers);
	}
	catch(const exception& e) {
		return error(404, "This host has not been found");
	}
	


	return error(404, "This Page has not been Found");
}
