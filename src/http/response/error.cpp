#include "response.hpp"

void replace_string(string& input, const string& pattern_in, const string& pattern_out);

string raw_error_file;
map<u_int32_t, string> error_codes_map;

void init_error_map(){
	// 4xx Client Error Responses
	error_codes_map[400] = "Bad Request";						// The request could not be understood or was missing required parameters.
	error_codes_map[401] = "Unauthorized";					// Authentication is required, and the user's credentials are missing or invalid.
	error_codes_map[402] = "Payment Required";				// Reserved for future use; not commonly used.
	error_codes_map[403] = "Forbidden";						// The server understood the request, but it refuses to fulfill it.
	error_codes_map[404] = "Not Found";						// The requested resource could not be found on the server.
	error_codes_map[405] = "Method Not Allowed";				// The HTTP method used in the request is not allowed for the requested resource.
	error_codes_map[406] = "Not Acceptable";					// The server cannot produce a response matching the list of acceptable values defined in the request's headers.
	error_codes_map[407] = "Proxy Authentication Required";	// Similar to 401, but the client must first authenticate itself with the proxy.
	error_codes_map[408] = "Request Timeout";					// The server timed out waiting for the request from the client.
	error_codes_map[409] = "Conflict";						// Indicates that there is a conflict with the current state of the resource.
	error_codes_map[410] = "Gone";							// The requested resource is no longer available at the server and will not be available again.
	error_codes_map[411] = "Length Required";					// The request did not specify the length of its content, which is required by the server.
	error_codes_map[412] = "Precondition Failed";				// One or more conditions in the request's headers were evaluated to false.
	error_codes_map[413] = "Payload Too Large";				// The request is larger than the server is willing or able to process.
	error_codes_map[414] = "URI Too Long";					// The URI provided in the request is too long for the server to process.
	error_codes_map[415] = "Unsupported Media Type";			// The server does not support the media type used in the request.
	error_codes_map[416] = "Range Not Satisfiable";			// The server cannot satisfy the range request specified in the request's headers.
	error_codes_map[417] = "Expectation Failed";				// The server cannot meet the requirements of the "Expect" header field in the request.

	// 5xx Server Error Responses
	error_codes_map[500] = "Internal Server Error";			// A generic error message indicating that an unexpected condition was encountered on the server.
	error_codes_map[501] = "Not Implemented";					// The server does not support the functionality required to fulfill the request.
	error_codes_map[502] = "Bad Gateway";						// The server, while acting as a gateway or proxy, received an invalid response from the upstream server.
	error_codes_map[503] = "Service Unavailable";				// The server is currently unable to handle the request due to temporary overloading or maintenance of the server.
	error_codes_map[504] = "Gateway Timeout";					// The server, while acting as a gateway or proxy, did not receive a timely response from the upstream server.
	error_codes_map[505] = "HTTP Version Not Supported";		// The server does not support the HTTP protocol version used in the request.
}

string error(u_int32_t code, const string& message){
	string error_file(raw_error_file);
	stringstream code_str; code_str << code;
	replace_string(error_file, "{{code}}", code_str.str());
	replace_string(error_file, "{{error_desc}}", error_codes_map[code]);
	if (message.length() > 0){
		replace_string(error_file, "{{error_message}}", message);
	}
	else {
		replace_string(error_file, "{{error_message}}", "");
	}
	Headers header;
	header["Content-Type"] = "text/html";

	cout << RED << "=>" << raw_error_file << RESET << endl;
	return get_response(code, header, error_file);
}

string error_serv(const Server& serv, u_int32_t code, const string& message){
	map<u_int32_t, string>::const_iterator look = serv.custom_error_page.find(code);
	if (look != serv.custom_error_page.end()){
		return look->second;
	}
	// if (serv.custom_error_page[code])
	return error(code, message);
}

map<u_int32_t, string>& get_codes_map(){
	return error_codes_map;
}

bool is_valid_error_code(u_int32_t code){
	return map_has_key(error_codes_map, code);
}
