#include "response.hpp"

void add_env(Env& env, const string& header, const string& value){
	env.push_back(header + "=" + value);
}

Env create_env(
	const Env& env,
	const Server& serv,
	const Location& loc,
	const string& cgi_bin,
	const string& filepath,
	const Request& req
){
	Env req_env(env);
	
	add_env(req_env, "SERVER_SOFTWARE", SERVER_VERSION);		// The name and version of hte server software.
	add_env(req_env, "SERVER_PROTOCOL", PROTOCOL);				// HTTP/1.1 / HTTP/2.0 ..
	add_env(req_env, "GATEWAY_INTERFACE", CGI_VERSION);			// CGI/1.1 CGI/2.0 ..

	add_env(req_env, "SERVER_NAME", serv.host);					// This meta variable holds domain / IP address to which the request was sent by the client.
	add_env(req_env, "SERVER_PORT", numberToString(serv.port));	// This meta variable holds port to which the request was sent by the client.

	add_env(req_env, "REQUEST_METHOD", req.method);				// GET POST PUT *PATCH* DELETE

	add_env(req_env, "SCRIPT_NAME", filepath);					// TODO verify this
	add_env(req_env, "SCRIPT_FILENAME", filepath);				// TODO verify this

	add_env(req_env, "REDIRECT_STATUS", "200");					// TODO verify this

	Headers::const_iterator ite = req.headers.find(HEADER_CONTENT_TYPE);
	if (ite != req.headers.end()){
		add_env(req_env, "CONTENT_TYPE", ite->second);		// TODO verify this
	}
	else {
		add_env(req_env, "CONTENT_TYPE", "text/plain");		// TODO verify this
	}

	if (!req.body.empty()){
		add_env(req_env, "CONTENT_LENGTH", numberToString(req.body.size()));		// TODO verify this
	}

	add_env(req_env, "PATH_INFO", req.path);
	// TODO verify this - The part of the request URI that succeeds the portion that locates the CGI script.									
	// For example, in the URI — http://localhost:8888/cgi/blog/posts/1 , PATH_INFO would be posts/1 which											
	// basically identifies an application specific resource to be interpreted by the individual cgi scripts.
	
	if (!req.param.empty()){
		add_env(req_env, "QUERY_STRING", req.param);
	}

	// add_env(req_env, "REMOTE_ADDR"); = "";
	// add_env(req_env, "REMOTE_HOST"); = "";

	// add_env(req_env, "CONTENT_LENGTH"); = "";
	// add_env(req_env, "CONTENT_TYPE"); = "";

	for (Env::const_iterator ite = req_env.begin(); ite != req_env.end(); ite++){
		cout << "=> " << *ite << endl; 
	}

	return req_env;
}