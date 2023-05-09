#include "Server.hpp"
#include "Request.hpp"

#include <stdlib.h>
#include <fcntl.h>

/* ************************************************************************** */

Server::Server():					server_fd(-1), connection_fd(-1), is_running(false), address(0, 80) { reset_buffer(); };
Server::Server(const Address& add): server_fd(-1), connection_fd(-1), is_running(false), address(add)   { reset_buffer(); };
Server::~Server() { stop(); }

/* ************************************************************************** */

void Server::reset_buffer() { memset(buffer, 0, BUFFER_SIZE); }

/* ************************************************************************** */



void Server::setup(){
	server_fd = socket(address.data.sin_family, SOCK_STREAM, 0);
	if (server_fd < 0)
		throw InternalError("failed to created socket server");
	
	int flags = fcntl(server_fd, F_GETFL, 0);
    if (flags < 0)
       throw InternalError("failed to retrieve the flags for server file descriptor");
	
    flags |= O_NONBLOCK;
    if (fcntl(server_fd, F_SETFL, flags) < 0)
       throw InternalError("failed to change flags for server file descriptor");
	
	int status = bind(server_fd, address.get_sockaddr(), address.len);
	if (status < 0)
		throw InternalError("failed to bind socket server to port");
	
	status = listen(server_fd, 256);
	if (status < 0)
		throw InternalError("failed to listen to socket server");
	
	cout << CYAN << "Listening on " << address << RESET << endl;
	is_running = true;
}



/**
 * @brief Stops the server instance
 */
void Server::stop(){
	if (!is_running)
		return ;
	is_running = false;
	if (server_fd >= 0){
		close(server_fd);
		server_fd = -1;
	}
	if (connection_fd >= 0){
		close(connection_fd);
		connection_fd = -1;
	}
	cout << endl << CYAN << "Closed " << address << RESET << endl;
}
