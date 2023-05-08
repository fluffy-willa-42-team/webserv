#include "Server.hpp"

/* ************************************************************************** */



void Server::start(){
	is_running = true;
	server_fd = socket(address.data.sin_family, SOCK_STREAM, 0);
	if (server_fd < 0)
		throw InternalError("failed to created socket server");
	int status = bind(server_fd, (struct sockaddr *)&address.data, sizeof(address.data));
	if (status < 0)
        throw InternalError("failed to bind socket server to port");
	status = listen(server_fd, 10);
	if (status < 0)
		throw InternalError("failed to listen to socket server");
	cout << "Listening on " << address << endl;
}

void Server::stop(){
	if (!is_running)
		return ;
	if (server_fd >= 0){
		close(server_fd);
		server_fd = -1;
	}
	if (connection_fd >= 0){
		close(connection_fd);
		connection_fd = -1;
	}
	cout << "Closed " << address << endl;
	is_running = false;
}



/* ************************************************************************** */




/*

socket()	create a file descriptor for a tcp connection
bind()		bind the socket to a specific port
listen()	sets the socket to a passiv mode and sets the number of connection that can wait in the backlog
accept()	sets the socket to a active mode and return a fd representing the connection.
			It will wait for the next connection or take the first in the backlog.
send()		write in the fd received in accept()
recv()		reads in the fd received in accept()

htons()		Format Port from human readable number to TCP port format for short number
htonl()		Format Port from human readable number to TCP port format for long number
ntohs()		Format Port from TCP port format to human readable number for short number
ntohl()		Format Port from TCP port format to human readable number for long number

*/