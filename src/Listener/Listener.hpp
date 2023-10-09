#ifndef LISTENER_HPP
# define LISTENER_HPP

/******************************************************************************/

#include "webserv.hpp"
#include "Config.hpp"
#include <netinet/in.h>
#include <poll.h>

/******************************************************************************/

class Listener {
	public:
		int32_t listener_fd;
		int32_t connection_fd;
		struct addrinfo *host;

		Listener();
		Listener(string host_ip, string port);
		~Listener();

		const string get_address();
};

/******************************************************************************/

#endif /* LISTENER_HPP */