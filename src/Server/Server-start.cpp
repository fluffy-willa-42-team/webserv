#include "Server.hpp"
#include "Request.hpp"

#include <fcntl.h>
#include <errno.h>

/* ************************************************************************** */

void Server::start(){
	setup();

	cout << GREEN << "----- Waiting for new connection (" << address << ") -----" << RESET << endl << endl;
	while(is_running)
	{
		connection_fd = accept(server_fd, NULL, NULL);
		if (connection_fd < 0 && errno == EWOULDBLOCK)
			continue ;
		if (connection_fd < 0){
			if (is_running){
				cout << is_running << " " << connection_fd << endl;
				throw InternalError();
			}
			return ;
		}
		
		exec();
		
		cout << GREEN << "----- Waiting for new connection (" << address << ") -----" << RESET << endl << endl;
	}
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