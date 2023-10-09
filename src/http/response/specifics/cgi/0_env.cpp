#include "response.hpp"

void add_env(Env& env, const string& header, const string& value){
	env.push_back(header + "=" + value);
}

Env create_env(
	const Env& env,
	const Server& serv,
	const string& filepath,
	const Request& req
){
	Env req_env(env);
	
	add_env(req_env, "SERVER_SOFTWARE", SERVER_VERSION);						// The name and version of hte server software.
	add_env(req_env, "SERVER_PROTOCOL", PROTOCOL);								// HTTP/1.1 / HTTP/2.0 ..
	add_env(req_env, "GATEWAY_INTERFACE", CGI_VERSION);							// CGI/1.1 CGI/2.0 ..

	add_env(req_env, "SERVER_NAME", serv.host);									// This meta variable holds domain / IP address to which the request was sent by the client.
	add_env(req_env, "SERVER_PORT", numberToString(serv.port));					// This meta variable holds port to which the request was sent by the client.

	add_env(req_env, "REQUEST_METHOD", req.method);								// GET POST PUT *PATCH* DELETE

	add_env(req_env, "SCRIPT_NAME", filepath);									
	add_env(req_env, "SCRIPT_FILENAME", filepath);								

	add_env(req_env, "REDIRECT_STATUS", numberToString(default_codes[req.method]));

	Headers::const_iterator ite = req.headers.find(HEADER_CONTENT_TYPE);
	if (ite != req.headers.end()){
		add_env(req_env, "CONTENT_TYPE", ite->second);							
	}
	else {
		add_env(req_env, "CONTENT_TYPE", "text/plain");							
	}

	if (!req.body.empty()){
		add_env(req_env, "CONTENT_LENGTH", numberToString(req.body.size()));	
	}

	add_env(req_env, "PATH_INFO", req.path);
	
	if (!req.param.empty()){
		add_env(req_env, "QUERY_STRING", req.param);
	}

	// add_env(req_env, "REMOTE_ADDR"); = "";
	// add_env(req_env, "REMOTE_HOST"); = "";

	// add_env(req_env, "CONTENT_LENGTH"); = "";
	// add_env(req_env, "CONTENT_TYPE"); = "";

	return req_env;
}