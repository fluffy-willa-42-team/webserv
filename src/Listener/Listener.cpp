#include "Listener.hpp"

#include <unistd.h>
#include "debug.hpp"

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
	DEBUG_INFO_() << "Try to close listener_fd: " << listener_fd;
	{
		if (listener_fd >= 0){
			const int check_close = close(listener_fd);
			if (check_close < 0){
				DEBUG_ERROR_() << "Failed to close listener_fd: " << listener_fd;
			}
			listener_fd = -1;
		}

	}
	DEBUG_() << "Listener closed";

	DEBUG_INFO_() << "Try to close connection_fd: " << connection_fd;
	{
		if (connection_fd >= 0){
			const int check_close = close(connection_fd);
			if (check_close < 0){
				DEBUG_ERROR_() << "Failed to close connection_fd: " << connection_fd;
			}
			connection_fd = -1;
		}
	}
	DEBUG_() << "connection_fd closed";

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
