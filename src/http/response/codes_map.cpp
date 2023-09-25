#include "response.hpp"

map<u_int32_t, string> codes_map;

void filter_codes_map(map<u_int32_t, string>& dest, u_int32_t hundredsDigit){
    for (map<u_int32_t, string>::const_iterator ite = codes_map.begin(); ite != codes_map.end(); ite++) {
        if ((ite->first % 100) == hundredsDigit) {
            dest[ite->first] = ite->second;
        }
    }
}

void init_codes_map(){
    // 1xx
	codes_map[100] = "Continue";						// The initial part of the request has been received, and the client should continue with its request.
    codes_map[101] = "Switching Protocols";				// The server is willing to change protocols, as requested by the client.
    
	// 2xx Redirections
	codes_map[200] = "OK";								// The request was successful, and the server has returned data.
    codes_map[201] = "Created";							// The request has been fulfilled, and a new resource has been created.
    codes_map[202] = "Accepted";						// The request has been accepted for processing, but the processing has not been completed.
    codes_map[203] = "Non-Authoritative Information";	// The server is a transforming proxy that received a 200 OK response from the origin server but is returning a modified version of the response.
    codes_map[204] = "No Content";						// The server has successfully processed the request but is not returning any content.
    codes_map[205] = "Reset Content";					// The server has fulfilled the request, and the client should reset the document view.
    codes_map[206] = "Partial Content";					// The server is delivering only part of the resource due to a range header sent by the client.
    
	// 3xx Redirections
	codes_map[300] = "Multiple Choices";				// The request has more than one possible response and the user or user agent can choose among them.
    codes_map[301] = "Moved Permanently";				// The requested resource has been permanently moved to a new URL.
    codes_map[302] = "Found";							// The requested resource has been temporarily found at a different URL.
    codes_map[303] = "See Other";						// The response to the request can be found under a different URL.
    codes_map[304] = "Not Modified";					// The requested resource has not been modified since the last requested time.
    codes_map[305] = "Use Proxy";						// The requested resource must be accessed through a proxy specified in the Location header.
    codes_map[307] = "Temporary Redirect";				// The request should be repeated with another URI, but the future requests should still use the original URI.
    
	// 4xx Client Error Responses
	codes_map[400] = "Bad Request";						// The request could not be understood or was missing required parameters.
    codes_map[401] = "Unauthorized";					// Authentication is required, and the user's credentials are missing or invalid.
    codes_map[402] = "Payment Required";				// Reserved for future use; not commonly used.
    codes_map[403] = "Forbidden";						// The server understood the request, but it refuses to fulfill it.
    codes_map[404] = "Not Found";						// The requested resource could not be found on the server.
    codes_map[405] = "Method Not Allowed";				// The HTTP method used in the request is not allowed for the requested resource.
    codes_map[406] = "Not Acceptable";					// The server cannot produce a response matching the list of acceptable values defined in the request's headers.
    codes_map[407] = "Proxy Authentication Required";	// Similar to 401, but the client must first authenticate itself with the proxy.
    codes_map[408] = "Request Timeout";					// The server timed out waiting for the request from the client.
    codes_map[409] = "Conflict";						// Indicates that there is a conflict with the current state of the resource.
    codes_map[410] = "Gone";							// The requested resource is no longer available at the server and will not be available again.
    codes_map[411] = "Length Required";					// The request did not specify the length of its content, which is required by the server.
    codes_map[412] = "Precondition Failed";				// One or more conditions in the request's headers were evaluated to false.
    codes_map[413] = "Payload Too Large";				// The request is larger than the server is willing or able to process.
    codes_map[414] = "URI Too Long";					// The URI provided in the request is too long for the server to process.
    codes_map[415] = "Unsupported Media Type";			// The server does not support the media type used in the request.
    codes_map[416] = "Range Not Satisfiable";			// The server cannot satisfy the range request specified in the request's headers.
    codes_map[417] = "Expectation Failed";				// The server cannot meet the requirements of the "Expect" header field in the request.
    
	// 5xx Server Error Responses
	codes_map[500] = "Internal Server Error";			// A generic error message indicating that the server encountered an unexpected condition that prevented it from fulfilling the request.
    codes_map[501] = "Not Implemented";					// The server does not support the functionality required to fulfill the request.
    codes_map[502] = "Bad Gateway";						// The server, while acting as a gateway or proxy, received an invalid response from the upstream server.
    codes_map[503] = "Service Unavailable";				// The server is currently unable to handle the request due to temporary overloading or maintenance of the server.
    codes_map[504] = "Gateway Timeout";					// The server, while acting as a gateway or proxy, did not receive a timely response from the upstream server or some other auxiliary server it needed to access in order to complete the request.
    codes_map[505] = "HTTP Version Not Supported";		// The server does not support the HTTP protocol version used in the request.

	filter_codes_map(redirect_codes_map, 300);
	filter_codes_map(error_codes_map, 400);
	filter_codes_map(error_codes_map, 500);
}