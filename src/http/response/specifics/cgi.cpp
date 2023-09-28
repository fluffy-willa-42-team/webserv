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

// Env create_env(
// 	const Server& serv,
// 	const Location& loc,
// 	const string& cgi_bin,
// 	const string& req_method,
// 	const string& req_path,
// 	const string& req_param
// ){
// 	Env env;

// 	env["SERVER_SOFTWARE"] = SERVER_VERSION;		// The name and version of hte server software.
// 	env["SERVER_PROTOCOL"] = PROTOCOL;				// HTTP/1.1 / HTTP/2.0 ..
// 	env["GATEWAY_INTERFACE"] = CGI_VERSION;			// CGI/1.1 CGI/2.0 ..

// 	env["SERVER_NAME"] = serv.host;					// This meta variable holds domain / IP address to which the request was sent by the client.
// 	env["SERVER_PORT"] = numberToString(serv.port);	// This meta variable holds port to which the request was sent by the client.

// 	env["REQUEST_METHOD"] = req_method;				// GET POST PUT *PATCH* DELETE

// 	env["SCRIPT_NAME"] = cgi_bin;					// TODO verify this
// 	env["SCRIPT_FILENAME"] = cgi_bin;				// TODO verify this

// 	env["PATH_INFO"] = req_path;
// 	// TODO verify this - The part of the request URI that succeeds the portion that locates the CGI script.									
// 	// For example, in the URI — http://localhost:8888/cgi/blog/posts/1 , PATH_INFO would be posts/1 which											
// 	// basically identifies an application specific resource to be interpreted by the individual cgi scripts.
// 	if (!req_param.empty()){
// 		env["QUERY_STRING"] = req_param;
// 	}

// 	// env["REMOTE_ADDR"] = "";
// 	// env["REMOTE_HOST"] = "";

// 	// env["CONTENT_LENGTH"] = "";
// 	// env["CONTENT_TYPE"] = "";

// 	for (Env::const_iterator ite = env.begin(); ite != env.end(); ite++){
// 		DEBUG_INFO_ << RED << ite->first << " = " << ite->second << RESET << endl;
// 	}

// 	return env;
// }

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