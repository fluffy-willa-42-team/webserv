#include <Post.hpp>

Post::Post(const Request& req, const Config& config) : Response(req, config){
	cout << PURPLE << "Constructing a POST method" << RESET << endl;
}

string Post::toString() const {
	stringstream res;
	res << PROTOCOL << " " << "[Status code]" << " " << "[Status Message]" << endl
		<< "Date: "				<< "[Date]"				<< endl
		<< "Server: "			<< "[Server name]"		<< endl
		<< "Content-Length: "	<< "[Content Length]"	<< endl
		<< "Content-Type: "		<< "[Content Type]"		<< endl;
	
	if (content)
	res << endl
		<< *content;
	
	return res.str();
}

/*

200 OK						: The request was successful, and the server returns the requested resource in the message body.
201 Created					: The server has successfully created a new resource as a result of the request, and it returns the newly created resource in the message body.
204 No Content				: The request was successful, but there is no data to return.
400 Bad Request				: The request was malformed or invalid, and the server cannot process it.
401 Unauthorized			: The client must authenticate itself before the server will process the request.
403 Forbidden				: The client does not have permission to access the requested resource.
404 Not Found				: The requested resource was not found on the server.
409 Conflict				: The request could not be completed due to a conflict with the current state of the resource.
500 Internal Server Error	: An error occurred on the server while processing the request.

*/