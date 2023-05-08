#ifndef SERVER_HPP
# define SERVER_HPP

/* ************************************************************************** */

#include <map>
#include <iomanip>
#include <unistd.h>
#include "using.hpp"
#include "Address.hpp"

/* ************************************************************************** */

# define BUFFER_SIZE 8000

/* ************************************************************************** */

class Server {
	private:
		bool	is_running;
		Address address;
		
		int32_t server_fd;
		char	buffer[BUFFER_SIZE];
	public:
		Server(const Address& add);
		~Server();

		void reset_buffer() { memset(buffer, 0, BUFFER_SIZE); }

		void start();

		class InternalError : public std::exception {
			public:
				string message;
				InternalError(): 						message("Server Internal Error"){}
				InternalError(const string& message): 	message("Server Internal Error"){ this->message += ": " + message; }
				~InternalError() throw() {}
				virtual const char* what() const throw() { return this->message.c_str(); }
		};
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