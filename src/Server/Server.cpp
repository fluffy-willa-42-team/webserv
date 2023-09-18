#include "Server.hpp"

#include <unistd.h>

Server::Server()
: port(0), server_fd(-1), connection_fd(-1), is_running(false)
{
	memset(&address_struct, 0, sizeof(address_struct));
	memset(buffer, 0, BUFFER_SIZE);
	address_struct.sin_port = htons(port);
}

Server::Server(u_int16_t port)
: port(port), server_fd(-1), connection_fd(-1), is_running(false)
{
	memset(&address_struct, 0, sizeof(address_struct));
	memset(buffer, 0, BUFFER_SIZE);
	address_struct.sin_port = htons(port);
}

Server::~Server(){
	if (server_fd >= 0){
		close(server_fd);
		server_fd = -1;
	}
	if (connection_fd >= 0){
		close(connection_fd);
		connection_fd = -1;
	}
}

const Server& Server::operator=(const Server& other)
{
	port = other.port;

	server_fd = -1;
	connection_fd = -1;

	is_running = false;

	memset(buffer, 0, sizeof(address_struct));
	memset(buffer, 0, BUFFER_SIZE);

	address_struct.sin_port = htons(port);

	return *this;
}
