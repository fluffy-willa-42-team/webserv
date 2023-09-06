#include "webserv.hpp"

static map<u_int32_t, string> codes;

map<u_int32_t, string>& get_codes_map(){
	return codes;
}

void init_error_map(){
	codes[400] = "Bad Request";
	codes[401] = "Unauthorized";
	codes[402] = "Payment Required";
	codes[403] = "Forbidden";
	codes[404] = "Not Found";
	codes[405] = "Method Not Allowed";
	codes[406] = "Not Acceptable";
	codes[407] = "Proxy Authentication Required";
	codes[408] = "Request Timeout";
	codes[409] = "Conflict";
	codes[410] = "Gone";
	codes[411] = "Length Required";
	codes[412] = "Precondition Failed";
	codes[413] = "Payload Too Large";
	codes[414] = "URI Too Long";
	codes[415] = "Unsupported Media Type";
	codes[416] = "Range Not Satisfiable";
	codes[417] = "Expectation Failed";

	codes[500] = "Internal Server Error";
	codes[501] = "Not Implemented";
	codes[502] = "Bad Gateway";
	codes[503] = "Service Unavailable";
	codes[504] = "Gateway Timeout";
	codes[505] = "HTTP Version Not Supported";
}