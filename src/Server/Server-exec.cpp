#include "Server.hpp"

#include <unistd.h>

const string http(const string& req);

void Server::exec(){
	read(connection_fd, buffer, BUFFER_SIZE);
	cout << CYAN << buffer << RESET << endl;

	// TODO Ensure the buffer has all the request

	string response = http(buffer);

	cout << response << endl;

	write(connection_fd , response.c_str(), response.length());
	
	memset(buffer, 0, BUFFER_SIZE);

	close(connection_fd);
}