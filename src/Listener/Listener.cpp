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
#include <sys/types.h>
#ifdef KOS_DARWIN
	#include <sys/event.h>
#endif
#include <sys/time.h>
#include "debug.hpp"


void print_address(const struct addrinfo *info) {
	if (info->ai_family == AF_INET) {
		struct sockaddr_in *addr = (struct sockaddr_in *)info->ai_addr;
		char ipstr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(addr->sin_addr), ipstr, INET_ADDRSTRLEN);

		cout << "IPv4 Address: " << ipstr << endl;
	} else if (info->ai_family == AF_INET6) {
		struct sockaddr_in6 *addr = (struct sockaddr_in6 *)info->ai_addr;
		char ipstr[INET6_ADDRSTRLEN];
		inet_ntop(AF_INET6, &(addr->sin6_addr), ipstr, INET6_ADDRSTRLEN);
		cout << "IPv6 Address: " << ipstr << endl;
	} else {
		cout << "Unknown address family" << endl;
	}
}

Listener::Listener()
: listener_fd(-1), connection_fd(-1), host(NULL)
{
}

Listener::Listener(string host_ip, string port)
: listener_fd(-1), connection_fd(-1), host(NULL) 
{
	// Need to catch exception to close socket and free c allocation by forcing destructor call
	try {
		struct addrinfo hints;

		memset(&hints, 0, sizeof(hints));
		// Set the family to IPv4
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;

		const int g_check = getaddrinfo(host_ip.c_str(), port.c_str(), &hints, &host);
		if (g_check != 0) {
			DEBUG_WARN_ << "getaddrinfo: " << gai_strerror(g_check) << endl;
			throw runtime_error("Invalid host: \"" + host_ip + "\"");
		}
		if (host == NULL){
			DEBUG_ERROR_ << "Failed to create socket, addrinfo is null?!" << endl;
			throw runtime_error("Failed to create socket");
		}

		if (host->ai_family == AF_INET) {
			struct sockaddr_in *addr = (struct sockaddr_in *)host->ai_addr;
			char ipstr[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &(addr->sin_addr), ipstr, INET_ADDRSTRLEN);
		} else {
			DEBUG_ERROR_ << "Non ipv4 address family" << endl;
			throw runtime_error("Non ipv4 address family");
		}

		// Create Socket file descriptor for server
		listener_fd = socket(host->ai_family, host->ai_socktype, host->ai_protocol);
		DEBUG_ << "listener_fd: " << listener_fd << endl;
		if (listener_fd < 0){
			DEBUG_ERROR_ << "Failed to create socket: errno: " << strerror(errno) << endl;
			throw runtime_error("Failed to create socket");
		}

		// retrieve the file descriptor flags
		int flags = fcntl(listener_fd, F_GETFL, 0);
		if (flags < 0){
			DEBUG_ERROR_ << "Failed to get socket flags: errno: " << strerror(errno) << endl;
			throw runtime_error("Failed to get socket flags");
		}
		
		// verify the file descriptor has the right O_NONBLOCK flag
		flags |= O_NONBLOCK;
		if (fcntl(listener_fd, F_SETFL, flags) < 0){
			DEBUG_ERROR_ << "Failed to set socket flags: errno: " << strerror(errno) << endl;
			throw runtime_error("Failed to set socket flags");
		}

		if (setsockopt(listener_fd, SOL_SOCKET, SO_REUSEADDR, &flags, sizeof(flags)) < 0){
			DEBUG_ERROR_ << "Failed to set socket options: errno: " << strerror(errno) << endl;
			throw runtime_error("Failed to set socket options");
		}

		if (bind(listener_fd, host->ai_addr, host->ai_addrlen) < 0){
			DEBUG_ERROR_ << "Failed to bind socket: errno: " << strerror(errno) << endl;
			throw runtime_error("Failed to bind socket");
		}

		// start to listens to port for new TCP connection
		if (listen(listener_fd, 1000) < 0){
			DEBUG_ERROR_ << "Failed to listen socket: errno: " << strerror(errno) << endl;
			throw runtime_error("Failed to listen socket");
		}
	} catch (const runtime_error& e) {
		this->~Listener();
		throw e;
	}

}

Listener::~Listener(){
	DEBUG_INFO_ << "Try to close listener_fd: " << listener_fd << endl;
	{
		if (listener_fd >= 0){
			const int check_close = close(listener_fd);
			if (check_close < 0){
				DEBUG_ << "Failed to close listener_fd: " << listener_fd << endl;
			}
			listener_fd = -1;
		}
	}

	DEBUG_INFO_ << "Try to close connection_fd: " << connection_fd << endl;
	{
		if (connection_fd >= 0){
			const int check_close = close(connection_fd);
			if (check_close < 0){
				DEBUG_ << "Failed to close connection_fd: " << connection_fd << endl;
			}
			connection_fd = -1;
		}
	}

	DEBUG_ << "Try to freeaddrinfo(host)" << endl;
	if (host){
		freeaddrinfo(host);
		host = NULL;
		DEBUG_INFO_ << "host addrinfo freed" << endl;
	} else {
		DEBUG_WARN_ << "host addrinfo is NULL" << endl;
	}
}
