#include "response.hpp"

bool is_file_cgi(const Location& loc, const string& filename, string& cgi_bin){
	for (map<string, string>::const_iterator ite = loc.cgi_pass.begin(); ite != loc.cgi_pass.end(); ite++){
		if (endsWith(filename, ite->first)){
			cgi_bin = ite->second;
			return true;
		}
	}
	return false;
}

Env create_env(
	const Env& env,
	const Server& serv,
	const Location& loc,
	const string& cgi_bin,
	const string& req_method,
	const string& req_path,
	const string& req_param
);

string exec_cgi(const Env& env, const string& cgi_bin){
	// execve()
	return "OK";
}

string cgi(
	const Env& env,
	const Server& serv,
	const Location& loc,
	const string& cgi_bin,
	const string& req_method,
	const string& req_path,
	const string& req_param,
	const string& filepath
){
	Env req_env = create_env(env, serv, loc, cgi_bin, req_method, req_path, req_param);

	cout << "CGI: " << cgi_bin << " | " << filepath << endl;
	Headers headers;
	return get_response(200, headers, ":D");
}