#ifndef LISTENER_HPP
# define LISTENER_HPP

/******************************************************************************/

#include "webserv.hpp"
#include "Config.hpp"
#include <netinet/in.h>
#include <poll.h>

/******************************************************************************/

# define BUFFER_SIZE 800

typedef struct {
	u_int32_t code;
	int32_t err; // TODO Remove
	string message;
}	t_setup;

/******************************************************************************/

class Listener {
	public:
		u_int16_t port;

		int32_t listener_fd;
		int32_t connection_fd;

		pollfd wpoll;
		sockaddr_in address_struct;

		Listener();
		Listener(in_addr address, u_int16_t port);
		~Listener();

		const Listener& operator=(const Listener& other);

		const string get_address();
};

/******************************************************************************/

#endif /* LISTENER_HPP */