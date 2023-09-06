#include "webserv.hpp"

static map<u_int32_t, string> codes;

map<u_int32_t, string>& get_codes_map(){
	return codes;
}

void init_error_map(){
	// 4xx Client Error Responses
	codes[400] = "Bad Request";						// The request could not be understood or was missing required parameters.
	codes[401] = "Unauthorized";					// Authentication is required, and the user's credentials are missing or invalid.
	codes[402] = "Payment Required";				// Reserved for future use; not commonly used.
	codes[403] = "Forbidden";						// The server understood the request, but it refuses to fulfill it.
	codes[404] = "Not Found";						// The requested resource could not be found on the server.
	codes[405] = "Method Not Allowed";				// The HTTP method used in the request is not allowed for the requested resource.
	codes[406] = "Not Acceptable";					// The server cannot produce a response matching the list of acceptable values defined in the request's headers.
	codes[407] = "Proxy Authentication Required";	// Similar to 401, but the client must first authenticate itself with the proxy.
	codes[408] = "Request Timeout";					// The server timed out waiting for the request from the client.
	codes[409] = "Conflict";						// Indicates that there is a conflict with the current state of the resource.
	codes[410] = "Gone";							// The requested resource is no longer available at the server and will not be available again.
	codes[411] = "Length Required";					// The request did not specify the length of its content, which is required by the server.
	codes[412] = "Precondition Failed";				// One or more conditions in the request's headers were evaluated to false.
	codes[413] = "Payload Too Large";				// The request is larger than the server is willing or able to process.
	codes[414] = "URI Too Long";					// The URI provided in the request is too long for the server to process.
	codes[415] = "Unsupported Media Type";			// The server does not support the media type used in the request.
	codes[416] = "Range Not Satisfiable";			// The server cannot satisfy the range request specified in the request's headers.
	codes[417] = "Expectation Failed";				// The server cannot meet the requirements of the "Expect" header field in the request.

	// 5xx Server Error Responses
	codes[500] = "Internal Server Error";			// A generic error message indicating that an unexpected condition was encountered on the server.
	codes[501] = "Not Implemented";					// The server does not support the functionality required to fulfill the request.
	codes[502] = "Bad Gateway";						// The server, while acting as a gateway or proxy, received an invalid response from the upstream server.
	codes[503] = "Service Unavailable";				// The server is currently unable to handle the request due to temporary overloading or maintenance of the server.
	codes[504] = "Gateway Timeout";					// The server, while acting as a gateway or proxy, did not receive a timely response from the upstream server.
	codes[505] = "HTTP Version Not Supported";		// The server does not support the HTTP protocol version used in the request.
}