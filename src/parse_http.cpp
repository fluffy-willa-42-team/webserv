#include "webserv.hpp"

#define response_example "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 112\n\n<html>\n<head>\n	<title>200 OK</title>\n	</head>\n	<body>\n		<h1>OK</h1>\n		<p>The request was successful.</p>\n	</body>\n</html>"

string error(u_int32_t code, const string& message);

const string parse_http(const string& req){
	// stringstream ss(req);
	// string line;

	// while (std::getline(ss, line) && line.length() > 0 && line != "\r"){
	// 	cout << line;
	// }
	// const string res = Error(404, "Not Found").http();
	return error(404, "Page not Found");
	// return "";
}