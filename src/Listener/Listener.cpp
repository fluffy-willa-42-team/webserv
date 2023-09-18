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
	if (listener_fd >= 0){
		close(listener_fd);
		listener_fd = -1;
	}
	if (connection_fd >= 0){
		close(connection_fd);
		connection_fd = -1;
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
