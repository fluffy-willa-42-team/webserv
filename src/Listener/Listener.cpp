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

void print_address(const struct addrinfo *info) {
    if (info->ai_family == AF_INET) {
        struct sockaddr_in *addr = (struct sockaddr_in *)info->ai_addr;
        char ipstr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(addr->sin_addr), ipstr, INET_ADDRSTRLEN);
        std::cout << "IPv4 Address: " << ipstr << std::endl;
    } else if (info->ai_family == AF_INET6) {
        struct sockaddr_in6 *addr = (struct sockaddr_in6 *)info->ai_addr;
        char ipstr[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &(addr->sin6_addr), ipstr, INET6_ADDRSTRLEN);
        std::cout << "IPv6 Address: " << ipstr << std::endl;
    } else {
        std::cout << "Unknown address family" << std::endl;
    }
}

Listener::Listener()
: listener_fd(-1), connection_fd(-1), host(NULL)
{
}

Listener::Listener(string host_ip, string port)
: listener_fd(-1), connection_fd(-1) 
{
	// DEBUG_INFO_ << "Try to create listener on: " << inet_ntoa(host->ai_addr) << ":" << port << endl;

	// DEBUG_ << "address_struct.sin_port: " << address_struct.sin_port << endl;
	// DEBUG_ << "port: " << port << endl;
	// DEBUG_ << "address_struct.sin_addr.s_addr: " << address_struct.sin_addr.s_addr << endl;
	// DEBUG_ << "address_struct.sin_addr: " << inet_ntoa(address_struct.sin_addr) << endl;
	// Check and store host ip
	// https://beej.us/guide/bgnet/html/#bind
	struct addrinfo hints;

	memset(&hints, 0, sizeof(hints));
	// Set the family to IPv4
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	// WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN
	// WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN
	// TOFIX gettaddrinfo alloc newServer.host_data, i remove the free in the destructor of Server.
	// TOFIX we need to rework the Config and Server class to fix this.
	// TOFIX The rework shold not be a class that pars, only use class to store final data.
	// WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN
	// WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN ! WARN
	const int g_check = getaddrinfo(host_ip.c_str(), port.c_str(), &hints, &host);
	if (g_check != 0) {
		DEBUG_WARN_ << "getaddrinfo: " << gai_strerror(g_check) << endl;
		throw std::runtime_error("Invalid host: \"" + host_ip + "\"");
	}
	if (host == NULL){
		DEBUG_ERROR_ << "Failed to create socket, addrinfo is null?!" << endl;
		throw std::runtime_error("Failed to create socket");
	}
	print_address(host);//TODO remove

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

	getsockname(listener_fd, host->ai_addr, &host->ai_addrlen);

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

	DEBUG_ << "Try to freeaddrinfo(host)" << endl;
	if (host){
		freeaddrinfo(host);
		host = NULL;
		DEBUG_INFO_ << "host addrinfo freed" << endl;
	} else {
		DEBUG_WARN_ << "host addrinfo is NULL" << endl;
	}
}

const Listener& Listener::operator=(const Listener& other)
{
	listener_fd = -1;
	connection_fd = -1;

	host = other.host;
	return *this;
}
