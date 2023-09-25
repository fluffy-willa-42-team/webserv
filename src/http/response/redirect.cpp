#include "response.hpp"

static map<u_int32_t, string> codes_map;

map<u_int32_t, string> redirect_codes_map;

void init_redirect_map(){
	// 3xx Redirection
	redirect_codes_map[300] = "Multiple Choices";	// The request has multiple possible responses, and the client should choose one."
	redirect_codes_map[301] = "Moved Permanently";	// The requested resource has been permanently moved to a different URL."
	redirect_codes_map[302] = "Found";				// The requested resource is temporarily located at a different URL."
	redirect_codes_map[303] = "See Other";			// The response to the request can be found at a different URL, and the client should perform a GET request to that URL."
	redirect_codes_map[304] = "Not Modified";		// The client's cached copy of the resource is still valid, and there is no need to re-fetch it."
	redirect_codes_map[307] = "Temporary Redirect";	// Similar to a 302, indicating that the resource is temporarily located at a different URL."
	redirect_codes_map[308] = "Permanent Redirect";	// Similar to a 301, indicating that the resource has been permanently moved to a different URL."
}

map<u_int32_t, string>& get_redirect_codes_map(){
	return redirect_codes_map;
}

bool is_valid_redirect_code(u_int32_t code){
	return map_has_key(redirect_codes_map, code);
}

string redirect(u_int32_t code, const string& path){
	Headers header;
	header[HEADER_REDIRECT] = path;
	return get_response(code, header);
}