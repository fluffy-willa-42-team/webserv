#include "response.hpp"

map<u_int32_t, string> redirect_codes_map;

bool is_valid_redirect_code(u_int32_t code){
	return map_has_key(redirect_codes_map, code);
}

string redirect(u_int32_t code, const string& path){
	Headers header;
	header[HEADER_REDIRECT] = path;
	return get_response(code, header);
}