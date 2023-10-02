#include "response.hpp"

Env create_env(const Env& env, const Server& serv, const Location& loc, const string& cgi_bin, const string& req_method, const string& req_path, const string& req_param, const string& filepath);
string exec_cgi(const Env& env, const string& cgi_bin, const string& file);
string parse_cgi_response(const string& cgi_response, uint32_t& code, Headers& headers, string& body);

bool is_file_cgi(const Location& loc, const string& filename, string& cgi_bin){
	for (map<string, string>::const_iterator ite = loc.cgi_pass.begin(); ite != loc.cgi_pass.end(); ite++){
		if (endsWith(filename, ite->first)){
			cgi_bin = ite->second;
			return true;
		}
	}
	return false;
}

string cgi(const Env& env,
	const Server& serv,
	const Location& loc,
	const string& cgi_bin,
	const string& req_method,
	const string& req_path,
	const string& req_param,
	const string& filepath
){
	Env req_env = create_env(env, serv, loc, cgi_bin, req_method, req_path, req_param, filepath);

	string cgi_response;
	try {
		cgi_response = exec_cgi(req_env, cgi_bin, filepath);
	}
	catch(const exception& e) {
		DEBUG_WARN_ << "CGI error: " << e.what() << endl;
		return error(500);
	}
	


	uint32_t code = 0;
	Headers headers;
	string body;

	string response = parse_cgi_response(cgi_response, code, headers, body);
	if (code < 100 || code >= 600){
		code = 200;
	}

	return get_response(code, headers, response);
}