#include "Listener.hpp"

#include <unistd.h>

Listener::Listener()
: port(0), listener_fd(-1), connection_fd(-1), is_running(false)
{
	memset(&address_struct, 0, sizeof(address_struct));
	memset(buffer, 0, BUFFER_SIZE);
	address_struct.sin_port = htons(port);
}

Listener::Listener(u_int16_t port)
: port(port), listener_fd(-1), connection_fd(-1), is_running(false)
{
	memset(&address_struct, 0, sizeof(address_struct));
	memset(buffer, 0, BUFFER_SIZE);
	address_struct.sin_port = htons(port);
}

Listener::~Listener(){
	{
		if (listener_fd >= 0){
			const int check_close = close(listener_fd);
			if (check_close < 0){
				std::cerr << "Error: Failed to close listener_fd: " << listener_fd << std::endl;
			}
			listener_fd = -1;
		}

	}
	{
		if (connection_fd >= 0){
			const int check_close = close(connection_fd);
			if (check_close < 0){
				std::cerr << "Error: Failed to close connection_fd: " << connection_fd << std::endl;
			}
			connection_fd = -1;
		}
	}

}

const Listener& Listener::operator=(const Listener& other)
{
	port = other.port;

	listener_fd = -1;
	connection_fd = -1;

	is_running = false;

	memset(buffer, 0, sizeof(address_struct));
	memset(buffer, 0, BUFFER_SIZE);

	address_struct.sin_port = htons(port);

	return *this;
}
