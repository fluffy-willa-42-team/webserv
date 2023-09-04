#include "Server.hpp"

#include <unistd.h>

Server::Server()
: address(0), port(0), server_fd(-1), connection_fd(-1), is_running(false)
{
	memset(buffer, 0, sizeof(address_struct));
	memset(buffer, 0, BUFFER_SIZE);
	address_struct.sin_addr.s_addr = address;
	address_struct.sin_port = port;
}

Server::Server(u_int32_t address, u_int16_t port)
: address(address), port(port), server_fd(-1), connection_fd(-1), is_running(false)
{
	memset(buffer, 0, sizeof(address_struct));
	memset(buffer, 0, BUFFER_SIZE);
	address_struct.sin_addr.s_addr = address;
	address_struct.sin_port = port;
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
	address = other.address;
	port = other.port;

	server_fd = -1;
	connection_fd = -1;

	is_running = false;

	memset(buffer, 0, sizeof(address_struct));
	memset(buffer, 0, BUFFER_SIZE);

	address_struct.sin_addr.s_addr = address;
	address_struct.sin_port = port;

	return *this;
}
