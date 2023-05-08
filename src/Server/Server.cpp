#include "Server.hpp"

void Server::start(){
	this->server_fd = socket(this->address.data.sin_family, SOCK_STREAM, 0);
	if (this->server_fd < 0)
		throw InternalError("failed to created socket server");
	
}

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