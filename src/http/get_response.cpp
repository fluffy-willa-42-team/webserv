#include "webserv.hpp"

map<u_int32_t, string>& get_codes_map();

static map<u_int32_t, string>& codes_map = get_codes_map();

string get_response(u_int32_t code, map<string, string> headers, string body){
	headers["Content-Length"] = body.length();

	const string description = codes_map[code];

	stringstream ss;
	ss << PROTOCOL << " " << code << " " << description << endl;
	for (map<string, string>::iterator ite = headers.begin(); ite != headers.end(); ite++){
		ss << ite->first << ": " << ite->second << endl;
	}
	ss << endl;
	ss << body;
	return ss.str();
}