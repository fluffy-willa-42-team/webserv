#include "Server.hpp"
#include "Request.hpp"
#include "Response.hpp"

void Server::exec(){
	read(connection_fd, buffer, BUFFER_SIZE);
	cout << CYAN << buffer << RESET << endl;

	Request req(buffer);

	if (!req.isValid()){
		cout << RED << "Invalid Request" << endl;
		return ;
	}

	Response* res = response_factory(req, config);
	if (!res)
		throw runtime_error("response is null");

	string message = res->toString();

	cout << message << endl;

	write(connection_fd , message.c_str(), message.length());
	
	reset_buffer();

	close(connection_fd);
}