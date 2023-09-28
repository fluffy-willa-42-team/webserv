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
#include <sys/event.h>
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
: listener_fd(-1), connection_fd(-1) 
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

		// getsockname(listener_fd, host->ai_addr, &host->ai_addrlen);

		//TODO WIP @Matthew-Dreemurr https://beej.us/guide/bgnet/html/split/system-calls-or-bust.html#listen
		// start to listens to port for new TCP connection
		if (listen(listener_fd, 1000) < 0){
			DEBUG_ERROR_ << "Failed to listen socket: errno: " << strerror(errno) << endl;
			throw runtime_error("Failed to listen socket");
		}

	} catch (const exception& e) {
		this->~Listener();
		throw e;
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

string Listener::read_buff(){
	//TODO WIP @Matthew-Dreemurr reade more doc about nonblocking I/O
	// https://www.ibm.com/docs/en/i/7.5?topic=designs-example-nonblocking-io-select
    int kq = kqueue();
	DEBUG_ << "Kqueue: " << kq << endl;
    if (kq == -1) {
		DEBUG_ERROR_ << "Failed to create kqueue: errno: " << strerror(errno) << endl;
		throw runtime_error("Failed to create kqueue");
        // handle error
    }

    struct kevent change;
    struct kevent event;

    EV_SET(&change, connection_fd, EVFILT_READ, EV_ADD, 0, 0, NULL);

    if (kevent(kq, &change, 1, &event, 1, NULL) == -1) {
        // handle error
		DEBUG_ERROR_ << "Failed to kevent: errno: " << strerror(errno) << endl;
		throw runtime_error("Failed to kevent");
    }

    if (event.flags & EV_EOF) {
        // handle EOF condition
		DEBUG_WARN_ << "EOF" << endl;
		throw runtime_error("EOF");
    } else if (event.flags & EV_ERROR) {
        // handle error reported in event
		DEBUG_WARN_ << "EV_ERROR" << endl;
		throw runtime_error("EV_ERROR");
    } else {
        memset(buffer, 0, BUFFER_SIZE);
        int32_t length_read = read(connection_fd, buffer, BUFFER_SIZE);
        if (length_read == -1){
            // handle read error
			DEBUG_ERROR_ << "Failed to read: errno: " << strerror(errno) << endl;
			throw runtime_error("Failed to read");
        }
		close (kq);
        return string(buffer, length_read);
    }
}

const Listener& Listener::operator=(const Listener& other)
{
	listener_fd = -1;
	connection_fd = -1;

	host = other.host;
	return *this;
}
