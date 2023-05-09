#include "Server.hpp"
#include "Request.hpp"

#include <fcntl.h>
#include <errno.h>

/* ************************************************************************** */

/**
 * @brief Will start a standalone server that is blocking. This is not meant to
 * be used for multiple server.
 */
void Server::start(){
	setup();

	cout << GREEN << "----- Waiting for new connection (" << address << ") -----" << RESET << endl << endl;
	while(is_running)
	{
		e_try res = try_connection();

		if (res == NO_CONNECTION)
			continue ;
		if (res == END_OF_RUNTIME)
			return ;		
		
		cout << GREEN << "----- Waiting for new connection (" << address << ") -----" << RESET << endl << endl;
	}
}



e_try Server::try_connection(){
	connection_fd = accept(server_fd, NULL, NULL);	// get new connection (non-blocking due to setup)
	if (connection_fd < 0 && errno == EWOULDBLOCK)	// check if there is a new connection
		return (NO_CONNECTION);
	if (connection_fd < 0){		// check if error in accept after having recieved a connection
		if (is_running){
			cout << is_running << " " << connection_fd << endl;
			throw InternalError();
		}
		return (END_OF_RUNTIME);
	}
	
	exec();
	return (SUCCESS);
}



void Server::setup(){
	is_running = true;
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
	
	cout << RED << "Listening on " << address << RESET << endl;
}