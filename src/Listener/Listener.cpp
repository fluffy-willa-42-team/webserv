#include "Listener.hpp"

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <cstdlib>
#include <fcntl.h>
#include <iomanip>
#include <netdb.h>

#include "debug.hpp"

Listener::Listener()
: listener_fd(-1), connection_fd(-1), host(NULL)
{
}

Listener::Listener(struct addrinfo *host)
: listener_fd(-1), connection_fd(-1), host(host)
{
	// DEBUG_INFO_ << "Try to create listener on: " << inet_ntoa(host->ai_addr) << ":" << port << endl;

	// DEBUG_ << "address_struct.sin_port: " << address_struct.sin_port << endl;
	// DEBUG_ << "port: " << port << endl;
	// DEBUG_ << "address_struct.sin_addr.s_addr: " << address_struct.sin_addr.s_addr << endl;
	// DEBUG_ << "address_struct.sin_addr: " << inet_ntoa(address_struct.sin_addr) << endl;

	

	// Create Socket file descriptor for server
	listener_fd = socket(host->ai_family, host->ai_socktype, host->ai_protocol);
	DEBUG_ << "listener_fd: " << listener_fd << endl;
	if (listener_fd < 0){
		DEBUG_ERROR_ << "Failed to create socket" << endl;
		throw std::runtime_error("Failed to create socket");
	}

	// retrieve the file descriptor flags
	int flags = fcntl(listener_fd, F_GETFL, 0);
	if (flags < 0){
		DEBUG_ERROR_ << "Failed to get socket flags" << endl;
		throw std::runtime_error("Failed to get socket flags");
	}
	
	// verify the file descriptor has the right O_NONBLOCK flag
	flags |= O_NONBLOCK;
	if (fcntl(listener_fd, F_SETFL, flags) < 0){
		DEBUG_ERROR_ << "Failed to set socket flags" << endl;
		throw std::runtime_error("Failed to set socket flags");
	}

	if (setsockopt(listener_fd, SOL_SOCKET, SO_REUSEADDR, &flags, sizeof(flags)) < 0){
		DEBUG_ERROR_ << "Failed to set socket options" << endl;
		throw std::runtime_error("Failed to set socket options");
	}

	if (bind(listener_fd, host->ai_addr, host->ai_addrlen) < 0){
		DEBUG_ERROR_ << "Failed to bind socket" << endl;
		throw std::runtime_error("Failed to bind socket");
	}

	//TODO WIP @Matthew-Dreemurr https://beej.us/guide/bgnet/html/split/system-calls-or-bust.html#listen
	// start to listens to port for new TCP connection
	if (listen(listener_fd, 10) < 0){
		DEBUG_ERROR_ << "Failed to listen socket" << endl;
		throw std::runtime_error("Failed to listen socket");
	}

	// Setup pollfd to listen to new connection with poll()

	wpoll.fd = listener_fd;
	wpoll.events = POLLIN;
	wpoll.revents = 0;
}

Listener::~Listener(){
	DEBUG_INFO_ << "Try to close listener_fd: " << listener_fd << endl;
	{
		if (listener_fd >= 0){
			const int check_close = close(listener_fd);
			if (check_close < 0){
				DEBUG_ERROR_ << "Failed to close listener_fd: " << listener_fd << endl;
			}
			listener_fd = -1;
		}
	}
	DEBUG_ << "Listener closed" << endl;

	DEBUG_INFO_ << "Try to close connection_fd: " << connection_fd << endl;
	{
		if (connection_fd >= 0){
			const int check_close = close(connection_fd);
			if (check_close < 0){
				DEBUG_ERROR_ << "Failed to close connection_fd: " << connection_fd << endl;
			}
			connection_fd = -1;
		}
	}
	DEBUG_ << "connection_fd closed" << endl;
}

const Listener& Listener::operator=(const Listener& other)
{
	port = other.port;

	listener_fd = -1;
	connection_fd = -1;

	address_struct = other.address_struct;

	return *this;
}
