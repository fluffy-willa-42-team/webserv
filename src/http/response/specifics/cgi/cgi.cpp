#include "response.hpp"

Env create_env(
	const Env& env,
	const Server& serv,
	const string& filepath,
	const Request& req
);

e_status exec_cgi(
	const Env& env,
	const string& cgi_bin,
	const string& req_body,
	const string& file,
	string& response
);

e_status parse_cgi_response(const string& cgi_response, uint32_t& code, Headers& headers, string& body);

bool is_file_cgi(const Location& loc, const string& filename, string& cgi_bin){
	for (map<string, string>::const_iterator ite = loc.cgi_pass.begin(); ite != loc.cgi_pass.end(); ite++){
		if (endsWith(filename, ite->first)){
			cgi_bin = ite->second;
			return true;
		}
	}
	return false;
}

string cgi(
	const Env& env,
	const Server& serv,
	const Location& loc,
	const string& cgi_bin,
	const string& filepath,
	const Request& req
){
	(void) loc;
	
	Env req_env = create_env(env, serv, filepath, req);

	string cgi_response;
	if (exec_cgi(req_env, cgi_bin, req.body, filepath, cgi_response) != S_CONTINUE){
		return error(500);
	}

	uint32_t code = 0;
	Headers headers;
	string body;

	if (parse_cgi_response(cgi_response, code, headers, body) != S_CONTINUE){
		return error(500);
	}
	if (code == 0){
		code = default_codes[req.method];
	}
	return get_response(code, headers, body);
}