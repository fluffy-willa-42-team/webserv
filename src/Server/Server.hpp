#ifndef SERVER_HPP
# define SERVER_HPP

/* ************************************************************************** */

#include <map>
#include <iomanip>
#include "using.hpp"
#include "Address.hpp"

/* ************************************************************************** */

class Server {
	private:
		Address address;
	public:
		Server(unsigned int address, unsigned int port) : address(address, port){
			cout << "Listening on " << this->address << endl;
		}

		Server(Address add) : address(add){
			cout << "Listening on " << this->address << endl;
		}
};

/* ************************************************************************** */

#endif /* SERVER_HPP */

/**

TCP
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


FD Managing
	select()	x
	poll()		x
	epoll()		x
	kqueue()	x

getaddrinfo
freeaddrinfo
setsockopt
getsockname
getprotobyname
gai_strerror

*/