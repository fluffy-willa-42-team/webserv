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

/*
CONTENT_LENGTH  —  This is the HTTP Content-Length header.
CONTENT_TYPE  —  The HTTP Content-Type header.

REMOTE_ADDR  —  This is the IP Address of the client which is sending the request.
REMOTE_HOST  —  If the client IP address can be mapped to a host name, this should be set with that else this can be set with the IP address itself.

QUERY_STRING  —  This contains the query string sent in the request URI.
*/
Env create_env(
	const Config& conf,
	const Server& serv,
	const Location& loc,
	const string& cgi_bin,
	const string& req_method,
	const string& req_path
){
	Env env;

	env["SERVER_SOFTWARE"] = SERVER_VERSION;		// The name and version of hte server software.
	env["SERVER_PROTOCOL"] = PROTOCOL;				// HTTP/1.1 / HTTP/2.0 ..
	env["GATEWAY_INTERFACE"] = CGI_VERSION;			// CGI/1.1 CGI/2.0 ..

	env["SERVER_NAME"] = serv.host;					// This meta variable holds domain / IP address to which the request was sent by the client.
	env["SERVER_PORT"] = serv.port;					// This meta variable holds port to which the request was sent by the client.

	env["REQUEST_METHOD"] = req_method;				// GET POST PUT *PATCH* DELETE

	env["SCRIPT_NAME"] = cgi_bin;					// TODO verify this
	env["SCRIPT_FILENAME"] = cgi_bin;				// TODO verify this

	env["PATH_INFO"] = req_path;					// TODO verify this - The part of the request URI that succeeds the portion that locates the CGI script.
													// For example, in the URI — http://localhost:8888/cgi/blog/posts/1 , PATH_INFO would be posts/1 which
													// basically identifies an application specific resource to be interpreted by the individual cgi scripts.

	// env["REMOTE_ADDR"] = "";
	// env["REMOTE_HOST"] = "";

	// env["CONTENT_LENGTH"] = "";
	// env["CONTENT_TYPE"] = "";

	return env;
}

string cgi(const string& cgi_bin, const string& filepath){
	cout << "CGI: " << cgi_bin << " | " << filepath << endl;
	Headers headers;
	return get_response(200, headers, ":D");
}