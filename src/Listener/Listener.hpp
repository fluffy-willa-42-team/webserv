#ifndef LISTENER_HPP
# define LISTENER_HPP

/******************************************************************************/

#include "webserv.hpp"
#include "Config.hpp"
#include <netinet/in.h>
#include <poll.h>

/******************************************************************************/

# define BUFFER_SIZE 800

/******************************************************************************/

class Listener {
	public:
		int32_t listener_fd;
		int32_t connection_fd;
		struct addrinfo *host;

		char buffer[BUFFER_SIZE];

		pollfd wpoll;

		Listener();
		Listener(string host_ip, string port);
		~Listener();

		const Listener& operator=(const Listener& other);

		const string get_address();
		string read_buff();
};

/******************************************************************************/

#endif /* LISTENER_HPP */