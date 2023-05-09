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

typedef enum {
	SUCCESS,
	NO_CONNECTION,
	END_OF_RUNTIME,
} e_try;

/* ************************************************************************** */

class Server {
	private:
		bool	is_running;
		Address address;
		
		int32_t server_fd;
		int32_t connection_fd;
		char	buffer[BUFFER_SIZE];


		void reset_buffer();
	public:
		Server();
		Server(const Address& add);
		~Server();

		void setup();
		void start();
		e_try try_connection();
		void exec();
		void stop();

		class InternalError : public std::exception {
			public:
				string message;
				InternalError(): 						message("Server Internal Error"){}
				InternalError(const string& message): 	message("Server Internal Error"){ this->message += ": " + message; }
				~InternalError() throw() {}
				virtual const char* what() const throw() { return message.c_str(); }
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