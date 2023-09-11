#include "Server.hpp"

#include <unistd.h>

const string http(const string& req, Server& server);

void Server::exec(){
	string buf = read_buff();
	cout << CYAN << buf << RESET << endl;

	// TODO Ensure the buffer has all the request

	string response = http(buf, *this);

	// cout << response << endl;

	write(connection_fd, response.c_str(), response.length());
	close(connection_fd);
}

string Server::read_buff(){
	memset(buffer, 0, BUFFER_SIZE);
	int32_t test = read(connection_fd, buffer, BUFFER_SIZE);
	cout << "read: " << test << endl;
	return string(buffer);
}