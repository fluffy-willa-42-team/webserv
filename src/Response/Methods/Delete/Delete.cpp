#include <Delete.hpp>

Delete::Delete(const Request& req, const Config& config) : Response(req, config){
	cout << PURPLE << "Constructing a DELETE method" << RESET << endl;
}

string Delete::toString() const {
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

200 OK						: The request was successful, and the server returns the deleted resource in the message body.
202 Accepted				: The server has accepted the request for processing, but the deletion may not be completed immediately.
204 No Content				: The request was successful, but there is no data to return.
400 Bad Request				: The request was malformed or invalid, and the server cannot process it.
401 Unauthorized			: The client must authenticate itself before the server will process the request.
403 Forbidden				: The client does not have permission to delete the requested resource.
404 Not Found				: The requested resource was not found on the server.
409 Conflict				: The request could not be completed due to a conflict with the current state of the resource.
500 Internal Server Error	: An error occurred on the server while processing the request.

*/