#include "http.hpp"
#include "response.hpp"

#include "debug.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

string clean_path(string req_path_param);

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
		DEBUG_ << "The Request is empty" << endl;
		return error(400, "The Request is empty");
	}
	removeCarriageReturn(line);

	vector<string> initline = split(line, " ");
	if (initline.size() != 3){
		DEBUG_ << "Init line is invalid" << endl;
		return error(400, "Init line is invalid");
	}


	// Method
	string req_method = initline[0];
	{
		DEBUG_INFO_ << "Method: " << req_method << endl;
		e_validation_status validation_status = is_method_valid(req_method);
		if (validation_status == NOT_ALLOWED){
			DEBUG_ << "Method is not allowed" << endl;
			return error(405);
		}
		else if (validation_status == BAD_REQUEST){
			DEBUG_ << "Method is invalid" << endl;
			return error(400, "Method is invalid");
		}
	}

	// Path + Param
	string req_path_param = initline[1];
	{
		DEBUG_INFO_ << "Path + Param: " << req_path_param << endl;
		if (!is_path_valid(req_path_param)){
			DEBUG_ << "Path is invalid" << endl;
			return error(400, "Path is invalid");
		}
	}

	// Protocol
	{
		string req_protocol = initline[2];
		DEBUG_INFO_ << "Protocol: " << req_protocol << endl;
		e_validation_status validation_status = is_method_valid(req_method);
		if (validation_status == NOT_ALLOWED){
			DEBUG_ << "Protocol is not allowed" << endl;
				return error(505); // HTTP Version not allowed
		}
		else if (validation_status == BAD_REQUEST){
			DEBUG_ << "Protocol is invalid" << endl;
			return error(400, "Protocol is invalid");

		}
	}





	/*===-----						Headers							   -----===*
	HEADER_KEY: HEADER_VALUE

	Ex:
	Accept-Language: en-US,en
	*/
	Headers req_headers;
    while (getline(ss_line_by_line, line) && removeCarriageReturn(line) && !line.empty()) {
		vector<string> headerline = splitFirst(line, ": ");
		if (is_header_valid(headerline) == BAD_REQUEST){
			DEBUG_ << "Headers are invalid" << endl;
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
	{
		if (!map_has_key(req_headers, string(HEADER_HOST))){
			DEBUG_ << "Missing host header" << endl;
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
				DEBUG_ << "Missing \"Content-Length\" header" << endl;
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
						DEBUG_ << "Invalid \"Content-Length\" header" << endl;
						return error(411, "Invalid \"Content-Length\" header");
					}
					req_body += buf;
				}
				DEBUG_INFO_ << "Req body: " << req_body;
			}
		}
	}





	/*===-----						XXXX							  -----===*/

	/*
	now that the request is parsed we now have to parse to config of all server
	to find the one that is valid and that worked an execute that.
	*/

	Server serv;
	try {
		serv = find_server(config, req_headers);
	}
	catch(const exception& e) {
		return error(404, "This host has not been found");
	}

	Location loc;
	try {
		loc = find_location(serv, req_path_param);
	}
	catch(const exception& e) {
		return error(404, "This Page has not been Found");
	}

	DEBUG_INFO_ << "Location: " << loc.path << endl;

	if (loc.type & E_NORMAL){
		string req_path = clean_path(req_path_param);
		string file_path = loc.root + req_path.substr(loc.path.size());
		if (loc.path == req_path){
			file_path = mergeFilePaths(loc.root, loc.index);
		}

		DEBUG_INFO_ << file_path << endl;

		struct stat path_info;
		if (stat(file_path.c_str(), &path_info) == -1) {
			if 		(errno == EACCES)	{ return error(403, "stat fail"); }
			else if (errno == ENOENT)	{ return error(404, "stat fail"); }
			else 						{ return error(500, "stat fail"); }
		}

		if (S_ISREG(path_info.st_mode)){ // Check if is file
			return get_file_res(file_path);
		}
		else if (S_ISDIR(path_info.st_mode)){ // Check if is folder
			if (!loc.autoindex){
				return error(404, "autoindex not activated");
			}
			return get_autoindex(req_path, file_path);
		}	
	}
	else if (loc.type & E_REDIRECT){
		return redirect(loc.redirect_code, loc.redirect_path);
	}
	
	// return test();
	return error(404, "This Page has not been Found");
}
