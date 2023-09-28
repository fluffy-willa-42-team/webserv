#include "response.hpp"

void add_env(Env& env, const string& header, const string& value){
	env.push_back(header + "=" + value);
	cout << env.size() << endl;
}

Env create_env(
	const Env& env,
	const Server& serv,
	const Location& loc,
	const string& cgi_bin,
	const string& req_method,
	const string& req_path,
	const string& req_param
){
	(void) env;
	(void) serv;
	(void) loc;
	(void) cgi_bin;
	(void) req_method;
	(void) req_path;
	(void) req_param;

	Env req_env(env);
	
	add_env(req_env, "SERVER_SOFTWARE", SERVER_VERSION);		// The name and version of hte server software.
	add_env(req_env, "SERVER_PROTOCOL", PROTOCOL);				// HTTP/1.1 / HTTP/2.0 ..
	add_env(req_env, "GATEWAY_INTERFACE", CGI_VERSION);			// CGI/1.1 CGI/2.0 ..

	add_env(req_env, "SERVER_NAME", serv.host);					// This meta variable holds domain / IP address to which the request was sent by the client.
	add_env(req_env, "SERVER_PORT", numberToString(serv.port));	// This meta variable holds port to which the request was sent by the client.

	add_env(req_env, "SERVER_SOFTWARE", SERVER_VERSION);
	add_env(req_env, "SERVER_SOFTWARE", SERVER_VERSION);

	add_env(req_env, "REQUEST_METHOD", req_method);				// GET POST PUT *PATCH* DELETE

	add_env(req_env, "SCRIPT_NAME", cgi_bin);					// TODO verify this
	add_env(req_env, "SCRIPT_FILENAME", cgi_bin);				// TODO verify this

	add_env(req_env, "PATH_INFO", req_path);
	// TODO verify this - The part of the request URI that succeeds the portion that locates the CGI script.									
	// For example, in the URI — http://localhost:8888/cgi/blog/posts/1 , PATH_INFO would be posts/1 which											
	// basically identifies an application specific resource to be interpreted by the individual cgi scripts.
	if (!req_param.empty()){
		add_env(req_env, "QUERY_STRING", req_param);
	}

	// add_env(req_env, "REMOTE_ADDR"); = "";
	// add_env(req_env, "REMOTE_HOST"); = "";

	// add_env(req_env, "CONTENT_LENGTH"); = "";
	// add_env(req_env, "CONTENT_TYPE"); = "";

	for (Env::const_iterator ite = req_env.begin(); ite != req_env.end(); ite++){
		cout << RED << *ite << RESET << endl;
	}

	return req_env;
}