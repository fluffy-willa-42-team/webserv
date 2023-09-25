#include "Listener.hpp"

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
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

Listener::Listener(std::string address, u_int16_t port)
: port(port), listener_fd(-1), connection_fd(-1), is_running(false)
{
	memset(&address_struct, 0, sizeof(address_struct));
	memset(buffer, 0, BUFFER_SIZE);
	address_struct.sin_addr.s_addr = inet_addr(address.c_str());
	address_struct.sin_port = htons(port);
	DEBUG_() << "address_struct.sin_port: " << address_struct.sin_port;
	DEBUG_() << "port: " << port;
	DEBUG_() << "address_struct.sin_addr.s_addr: " << address_struct.sin_addr.s_addr;
	DEBUG_() << "address_struct.sin_addr: " << inet_ntoa(address_struct.sin_addr);

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

	is_running = false;

	memset(buffer, 0, sizeof(address_struct));
	memset(buffer, 0, BUFFER_SIZE);

	address_struct.sin_port = htons(port);

	return *this;
}
