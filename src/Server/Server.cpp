#include "Server.hpp"
#include "Request.hpp"

#include <stdlib.h>

/* ************************************************************************** */

Server::Server():					is_running(false), address(0, 80), server_fd(-1), connection_fd(-1) { reset_buffer(); };
Server::Server(const Address& add): is_running(false), address(add),   server_fd(-1), connection_fd(-1) { reset_buffer(); };
Server::~Server() { stop(); }

/* ************************************************************************** */

void Server::reset_buffer() { memset(buffer, 0, BUFFER_SIZE); }

/* ************************************************************************** */

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
	cout << endl << RED << "Closed " << address << RESET << endl;
}
