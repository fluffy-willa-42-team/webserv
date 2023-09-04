#include "Server.hpp"

#include <unistd.h>

void Server::exec(){
	read(connection_fd, buffer, BUFFER_SIZE);
	cout << CYAN << buffer << RESET << endl;

	string message = buffer;

	cout << message << endl;

	write(connection_fd , message.c_str(), message.length());
	
	memset(buffer, 0, BUFFER_SIZE);

	close(connection_fd);
}