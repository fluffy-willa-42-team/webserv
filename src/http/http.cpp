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

e_status ret(e_status status, Request& req, const string& response){
	req.response = response;
	return status;
}

e_status parse_header(const Config& config, Request& req){
	stringstream ss_line_by_line(req.raw);
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
		return ret(S_STOP, req, error(400, "The Request is empty"));
	}
	removeCarriageReturn(line);

	vector<string> initline = split(line, " ");
	if (initline.size() != 3){
		DEBUG_ << "Init line is invalid" << endl;
		return ret(S_STOP, req, error(400, "Init line is invalid"));
	}


	// Method
	req.method = initline[0];
	{
		DEBUG_INFO_ << "Method: " << req.method << endl;
		e_validation_status validation_status = is_method_valid(req.method);
		if (validation_status == NOT_ALLOWED){
			DEBUG_ << "Method is not allowed" << endl;
			return ret(S_STOP, req, error(405));
		}
		else if (validation_status == BAD_REQUEST){
			DEBUG_ << "Method is invalid" << endl;
			return ret(S_STOP, req, error(400, "Method is invalid"));
		}
	}

	// Path + Param
	{
		string req_path_param = initline[1];
		if (!is_path_valid(req_path_param)){
			DEBUG_ << "Path is invalid" << endl;
			return ret(S_STOP, req, error(400, "Path is invalid"));
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
			return ret(S_STOP, req, error(505)); // HTTP Version not allowed
		}
		else if (validation_status == BAD_REQUEST){
			DEBUG_ << "Protocol is invalid" << endl;
			return ret(S_STOP, req, error(400, "Protocol is invalid"));
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
			return ret(S_STOP, req, error(400, "Headers are invalid"));
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
			return ret(S_STOP, req, error(400, "Missing host header"));
		}
	}





	/*===-----			Find Server and Location to execute			  -----===*\

	now that the request is parsed we now have to parse to config of all server
	to find the one that is valid and that worked an execute that.

	*/

	try {
		req.serv = find_server(config, req.headers);
	}
	catch(const exception& e) {
		return ret(S_STOP, req, error(404, "This host has not been found"));
	}

	try {
		req.loc = find_location(req.serv, req.path);
	}
	catch(const exception& e) {
		return ret(S_STOP, req, error_serv(req.serv, 404, NOT_FOUND_DESCRIPTION));
	}

	DEBUG_INFO_ << "Location: " << req.loc.path << endl;

	if (!vec_has(req.loc.allowed_methods, req.method)){
		return ret(S_STOP, req, error_serv(req.serv, 404));
	}





	stringstream remainingContentStream;
	remainingContentStream << ss_line_by_line.rdbuf();
	req.body = remainingContentStream.str();
	return S_CONTINUE;
}

/*===-----					Execute the Location found				  -----===*\
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
e_status execute_request(const Config& config, const Env& env, Request& req){
	if (req.method == "GET"){
		if (!req.loc.root.empty()){
			string file_path = req.loc.root + "/" + req.path.substr(req.loc.path.size());
			DEBUG_INFO_ << file_path << endl;
			if (!req.loc.index.empty() && req.loc.path == req.path){
				file_path = mergeFilePaths(req.loc.root, req.loc.index);
			}

			DEBUG_INFO_ << file_path << endl;

			struct stat path_info;
			if (stat(file_path.c_str(), &path_info) == -1) {
				return ret(S_STOP, req, error_serv(req.serv, 404, NOT_FOUND_DESCRIPTION));
			}

			if (S_ISREG(path_info.st_mode)){ // Check if is file
				if (!req.loc.cgi_pass.empty()){
					string cgi_bin;
					if (is_file_cgi(req.loc, file_path, cgi_bin)){
						return ret(S_STOP, req, cgi(env, req.serv, req.loc, cgi_bin, file_path, req));
					}
				}
				return ret(S_STOP, req, get_file_res(file_path, req.loc.download));
			}
			else if (S_ISDIR(path_info.st_mode)){ // Check if is folder
				if (!req.loc.autoindex){
					return ret(S_STOP, req, error_serv(req.serv, 404, NOT_FOUND_DESCRIPTION));
				}
				return ret(S_STOP, req, get_autoindex(req.path, file_path));
			}
			else {
				return ret(S_STOP, req, error_serv(req.serv, 403, "Only files and folder are allowed to be read"));
			}
		}
		else if (!req.loc.index.empty()){
			if (req.path != req.loc.path){
				return ret(S_STOP, req, error_serv(req.serv, 404, NOT_FOUND_DESCRIPTION));
			}
			if (!req.loc.cgi_pass.empty()){
				string cgi_bin;
				if (is_file_cgi(req.loc, req.loc.index, cgi_bin)){
					return ret(S_STOP, req, cgi(env, req.serv, req.loc, cgi_bin, req.loc.index, req));
				}
			}
			return ret(S_STOP, req, get_file_res(req.loc.index, req.loc.download));
		}
		else if (req.loc.redirect_code != 0){
			return ret(S_STOP, req, redirect(req.loc.redirect_code, req.loc.redirect_path));
		}
	}
	else if (req.method == "POST" || req.method == "PUT" || req.method == "DELETE"){
		string file_path = req.loc.root + "/" + req.path.substr(req.loc.path.size());
		if (!req.loc.index.empty() && req.loc.path == req.path){
			file_path = mergeFilePaths(req.loc.root, req.loc.index);
		}
		if (req.loc.cgi_pass.empty()){
			return ret(S_STOP, req, error(404, NOT_FOUND_DESCRIPTION));
		}
		string cgi_bin;
		if (!is_file_cgi(req.loc, file_path, cgi_bin)){
			return ret(S_STOP, req, error(404, NOT_FOUND_DESCRIPTION));
		}
		return ret(S_STOP, req, cgi(env, req.serv, req.loc, cgi_bin, file_path, req));
	}

	return ret(S_STOP, req, error_serv(req.serv, 404, NOT_FOUND_DESCRIPTION));
}

const string http(const int fd, const Config& config, const Env& env){
	Request req;

	try {
		req.raw += read_buff(fd);
	}
	catch(const exception& e) {
		DEBUG_ << "The Request is empty" << endl;
		return error(400, "The Request is empty");
	}
	
	{
		u_int32_t verif = 0;
		while (req.raw.find("\r\n\r\n") == string::npos){
			try {
				string new_cont = read_buff(fd);
				req.raw += new_cont;
				if (new_cont.length() == 0){
					verif++;
					if (verif > 100){
						DEBUG_ << "The Request timed out" << endl;
						return error(408);
					}
				}
			}
			catch(const exception& e) {
				return error(400);
			}
		}
	}

	DEBUG_ << "Request: " << endl << BLUE << req.raw << RESET << endl;

	
	//// PART 1
	{
		e_status status = parse_header(config, req);
		if (status == S_STOP){
			return req.response;
		}
	}

	/*===-----						Body							  -----===*/
	if (req.method == "POST" || req.method == "PUT" || req.method == "PATCH" || req.method == "DELETE")
	{
		if (map_has_key(req.headers, string(HEADER_CONTENT_LENGTH))){
			

			u_int32_t content_length = stringToNumber(req.headers[HEADER_CONTENT_LENGTH]);
			
			u_int32_t verif = 0;
			while (req.body.length() < content_length){
				if (req.serv.has_max_body_size_been_set && req.serv.max_body_size < (u_int32_t) req.body.size()){
					return error_serv(req.serv, 413);
				}
				try {
					string new_cont = read_buff(fd);
					req.body += new_cont;
					if (new_cont.length() == 0){
						verif++;
						if (verif > 100){
							DEBUG_ << "The Request timed out" << endl;
							return error(408);
						}
					}
				}
				catch(const exception& e) {
					DEBUG_ << "Fail Readbuf in body" << endl;
					return error_serv(req.serv, 400);
				}
			}
		}
	}


	//// PART 2
	execute_request(config, env, req);
	return req.response;
}
