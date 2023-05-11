#include <Get.hpp>

Get::Get(const Request& req, const Config& config) : Response(req, config){
	cout << PURPLE << "Constructing a GET method" << RESET << endl;
}

string Get::toString() const {
	stringstream res;
		res << PROTOCOL << " " << 200 << " " << "OK" << endl
			<< "Date: " << get_now() << endl
			<< "Server: " << config.name;
	
	if (content)
		res	<< endl << *content;
	return res.str();
}

/*

200 OK						: The request was successful, and the requested resource is returned in the message body.
204 No Content				: The request was successful, but there is no data to return.
301 Moved Permanently		: The requested resource has moved permanently to a new location, and the client should use the new URL for future requests.
302 Found					: The requested resource has moved temporarily to a new location, and the client should use the new URL for future requests.
304 Not Modified			: The requested resource has not been modified since the last time it was accessed, and the server does not need to send the resource again.
400 Bad Request				: The request was malformed or invalid, and the server cannot process it.
401 Unauthorized			: The client must authenticate itself before the server will process the request.
403 Forbidden				: The client does not have permission to access the requested resource.
404 Not Found				: The requested resource was not found on the server.
500 Internal Server Error	: An error occurred on the server while processing the request.

*/