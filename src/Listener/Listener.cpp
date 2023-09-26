#include "Listener.hpp"

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <cstdlib>
#include <fcntl.h>
#include <iomanip>

#include "debug.hpp"

Listener::Listener()
: port(0), listener_fd(-1), connection_fd(-1)
{
}

Listener::Listener(in_addr address, u_int16_t port)
: port(port), listener_fd(-1), connection_fd(-1)
{
	DEBUG_INFO_ << "Try to create listener on: " << inet_ntoa(address) << ":" << port << endl;

	// Setup address_struct
	// https://web.archive.org/web/20230609152403/https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html
	address_struct.sin_family = AF_INET;
	address_struct.sin_port = htons(port);
	// Host ip value is check in the config parser
	address_struct.sin_addr = address;

	DEBUG_ << "address_struct.sin_port: " << address_struct.sin_port << endl;
	DEBUG_ << "port: " << port << endl;
	DEBUG_ << "address_struct.sin_addr.s_addr: " << address_struct.sin_addr.s_addr << endl;
	DEBUG_ << "address_struct.sin_addr: " << inet_ntoa(address_struct.sin_addr) << endl;

	// Create Socket file descriptor for server
	listener_fd = socket(AF_INET, SOCK_STREAM, 0);
	DEBUG_ << "listener_fd: " << listener_fd << endl;

	if (listener_fd < 0){
		DEBUG_ERROR_ << "Failed to create socket" << endl;
		throw std::runtime_error("Failed to create socket");
	}

	// retrieve the file descriptor flags
	int flags = fcntl(listener_fd, F_GETFL, 0);
    if (flags < 0){
	}
	
	// verify the file descriptor has the right O_NONBLOCK flag
	flags |= O_NONBLOCK;
	if (fcntl(listener_fd, F_SETFL, flags) < 0){
	}

	if (setsockopt(listener_fd, SOL_SOCKET, SO_REUSEADDR, &flags, sizeof(flags)) < 0){
		DEBUG_ERROR_ << "Failed to set socket options" << endl;
		throw std::runtime_error("Failed to set socket options");
	}

	if (bind(listener_fd, (sockaddr*)&address_struct, sizeof(address_struct)) < 0){
		DEBUG_ERROR_ << "Failed to bind socket" << endl;
		throw std::runtime_error("Failed to bind socket");
	}

	// listens to port for new TCP connection

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
