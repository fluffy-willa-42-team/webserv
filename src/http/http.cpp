#include "webserv.hpp"

#define response_example "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 112\n\n<html>\n<head>\n	<title>200 OK</title>\n	</head>\n	<body>\n		<h1>OK</h1>\n		<p>The request was successful.</p>\n	</body>\n</html>"

string error(u_int32_t code, const string& message);

const string http(const string& req){
	// Parse_request() => return a struct or a class for a request with : path header protocol body 
	// Try and execute the right content for the request (CGI file ou redirection)
	return error(404, "This Page has not been Found");
}