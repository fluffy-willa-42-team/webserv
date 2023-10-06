#include "http.hpp"
#include "response.hpp"

#include "debug.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

string remove_end_backslash(string req_path_param);
string remove_param(string req_path_param);

string read_buff(int connection_fd){
	static char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);

	int32_t length_read = recv(connection_fd, buffer, BUFFER_SIZE, 0);
	if (length_read == -1){
		DEBUG_WARN_ << "Failed to read from socket: errno: " << strerror(errno) << endl;
		throw exception();
	}

	return string(buffer, length_read);
}

const string http(const int fd, const Config& config, const Env& env){
	string req_raw;

	try {
		req_raw += read_buff(fd);
	}
	catch(const exception& e) {
		DEBUG_ << "The Request is empty" << endl;
		return error(400, "The Request is empty");
	}
	
	while (req_raw.find("\r\n\r\n") == string::npos){
		try {
			req_raw += read_buff(fd);
		}
		catch(const exception& e) {
			return error(400);
		}
	}

	DEBUG_ << "Request: " << endl << BLUE << req_raw << RESET << endl;

	stringstream ss_line_by_line(req_raw);
	string line;

	Request req;

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
	req.method = initline[0];
	{
		DEBUG_INFO_ << "Method: " << req.method << endl;
		e_validation_status validation_status = is_method_valid(req.method);
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
	{
		string req_path_param = initline[1];
		if (!is_path_valid(req_path_param)){
			DEBUG_ << "Path is invalid" << endl;
			return error(400, "Path is invalid");
		}
		if (req_path_param.find_first_of('?') != string::npos){
			req.path = remove_end_backslash(req_path_param.substr(0, req_path_param.find_first_of('?')));
			req.param = req_path_param.substr(req_path_param.find_first_of('?') + 1, req_path_param.size());
			DEBUG_INFO_ << "Path + Param: " << req.path << " ? " << req.param << endl;
		}
		else {
			req.path = remove_end_backslash(req_path_param);
		}
		DEBUG_INFO_ << "Path: " << req.path << endl;
		DEBUG_INFO_ << "Param: " << req.param << endl;
	}

	// Protocol
	{
		string req_protocol = initline[2];
		DEBUG_INFO_ << "Protocol: " << req_protocol << endl;
		e_validation_status validation_status = is_method_valid(req.method);
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
    while (getline(ss_line_by_line, line) && removeCarriageReturn(line) && !line.empty()) {
		vector<string> headerline = splitFirst(line, ": ");
		if (is_header_valid(headerline) == BAD_REQUEST){
			DEBUG_ << "Headers are invalid" << endl;
			return error(400, "Headers are invalid");
		}
        req.headers[headerline[0]] = headerline[1];
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
		if (!map_has_key(req.headers, string(HEADER_HOST))){
			DEBUG_ << "Missing host header" << endl;
			return error(400, "Missing host header");
		}
	}





	/*===-----			Find Server and Location to execute			  -----===*\

	now that the request is parsed we now have to parse to config of all server
	to find the one that is valid and that worked an execute that.

	*/

	Server serv;
	try {
		serv = find_server(config, req.headers);
	}
	catch(const exception& e) {
		return error(404, "This host has not been found");
	}

	Location loc;
	try {
		loc = find_location(serv, req.path);
	}
	catch(const exception& e) {
		return error_serv(serv, 404, NOT_FOUND_DESCRIPTION);
	}

	DEBUG_INFO_ << "Location: " << loc.path << endl;

	if (!vec_has(loc.allowed_methods, req.method)){
		return error_serv(serv, 404);
	}





	/*===-----						Body							  -----===*/
	if (req.method == "POST" || req.method == "PUT" || req.method == "PATCH" || req.method == "DELETE")
	{
		if (map_has_key(req.headers, string(HEADER_CONTENT_LENGTH))){
			stringstream remainingContentStream;
			remainingContentStream << ss_line_by_line.rdbuf();
			req.body = remainingContentStream.str();

			u_int32_t content_length = stringToNumber(req.headers[HEADER_CONTENT_LENGTH]);
			
			while (req.body.length() < content_length){
				if (serv.has_max_body_size_been_set && serv.max_body_size < (u_int32_t) req.body.size()){
					return error_serv(serv, 413);
				}
				try {
					req.body += read_buff(fd);
				}
				catch(const exception& e) {
					DEBUG_ << "Invalid \"Content-Length\" header" << endl;
					return error_serv(serv, 411, "Invalid \"Content-Length\" header");
				}
			}
		}
	}




	/*===-----				Execute the Location found				  -----===*\
	
	Now that we have the right Location and Server to execute, we will find the
	right method and the right response to generate.

	Pseudo code:

	switch (req.method){
		case "GET": {
			switch (loc_type) {
				case IS_FOLDER: {
					if (file_is_cgi){
						return CGI_response();
					}
					else if (get_file()){
						return file_reponse();
					}
					else if (loc.autoindex){
						return autoindex_response();
					}
				}
				case IS_FILE: {
					if (file_is_cgi){
						return CGI_response();
					}
					return file_reponse();
				}
				case IS_REDIRECT: {
					return redirect_response();
				}
			}
		}
		case "POST": {
			return CGI_response();
		}
		case "PUT": {
			return CGI_response();
		}
		case "DELETE": {
			return CGI_response();
		}
	}

	*/

	if (req.method == "GET"){
		if (!loc.root.empty()){
			string file_path = loc.root + "/" + req.path.substr(loc.path.size());
			DEBUG_INFO_ << file_path << endl;
			if (!loc.index.empty() && loc.path == req.path){
				file_path = mergeFilePaths(loc.root, loc.index);
			}

			DEBUG_INFO_ << file_path << endl;

			struct stat path_info;
			if (stat(file_path.c_str(), &path_info) == -1) {
				return error_serv(serv, 404, NOT_FOUND_DESCRIPTION);
			}

			if (S_ISREG(path_info.st_mode)){ // Check if is file
				if (!loc.cgi_pass.empty()){
					string cgi_bin;
					if (is_file_cgi(loc, file_path, cgi_bin)){
						return cgi(env, serv, loc, cgi_bin, file_path, req);
					}
				}
				return get_file_res(file_path, loc.download);
			}
			else if (S_ISDIR(path_info.st_mode)){ // Check if is folder
				if (!loc.autoindex){
					return error_serv(serv, 404, NOT_FOUND_DESCRIPTION);
				}
				return get_autoindex(req.path, file_path);
			}
			else {
				return error_serv(serv, 403, "Only files and folder are allowed to be read");
			}
		}
		else if (!loc.index.empty()){
			if (req.path != loc.path){
				return error_serv(serv, 404, NOT_FOUND_DESCRIPTION);
			}
			if (!loc.cgi_pass.empty()){
				string cgi_bin;
				if (is_file_cgi(loc, loc.index, cgi_bin)){
					return cgi(env, serv, loc, cgi_bin, loc.index, req);
				}
			}
			return get_file_res(loc.index, loc.download);
		}
		else if (loc.redirect_code != 0){
			return redirect(loc.redirect_code, loc.redirect_path);
		}
	}
	else if (req.method == "POST" || req.method == "PUT" || req.method == "DELETE"){
		string file_path = loc.root + "/" + req.path.substr(loc.path.size());
		if (loc.cgi_pass.empty()){
			return error(404, NOT_FOUND_DESCRIPTION);
		}
		string cgi_bin;
		if (!is_file_cgi(loc, file_path, cgi_bin)){
			return error(404, NOT_FOUND_DESCRIPTION);
		}
		return cgi(env, serv, loc, cgi_bin, file_path, req);
	}

	return error_serv(serv, 404, NOT_FOUND_DESCRIPTION);
}
