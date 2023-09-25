#include "response.hpp"

string get_response(u_int32_t code, Headers headers, string body){
	stringstream length_str;
	length_str << body.length();
	headers["Content-Length"] = length_str.str();

	const string description = codes_map[code];

	stringstream ss;
	ss << PROTOCOL << " " << code << " " << description << endl;
	for (Headers::iterator ite = headers.begin(); ite != headers.end(); ite++){
		ss << ite->first << ": " << ite->second << endl;
	}
	ss << endl;
	if (!body.empty()){
		ss << body;
	}
	return ss.str();
}
