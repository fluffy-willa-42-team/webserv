#include "Server.hpp"
#include "Request.hpp"
#include "Response.hpp"

void Server::exec(){
	read(connection_fd, buffer, BUFFER_SIZE);
	cout << buffer << endl;

	Request req(buffer);

	Response* res = response_factory(req, config);
	if (!res)
		throw runtime_error("response is null");

	string message = res->toString();

	cout << message << endl;

	write(connection_fd , message.c_str(), message.length());
	
	reset_buffer();

	close(connection_fd);
}