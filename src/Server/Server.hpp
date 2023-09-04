#ifndef XXX
# define XXX

/******************************************************************************/

#include "webserv.hpp"
#include <netinet/in.h>

/******************************************************************************/

# define BUFFER_SIZE 8000

typedef struct {
	u_int32_t code;
	int32_t err;
	string message;
}	t_setup;

/******************************************************************************/

class Server {
	private:
		sockaddr_in address_struct;

		const u_int32_t address;
		const u_int16_t port;

		int32_t server_fd;
		int32_t connection_fd;
		char	buffer[BUFFER_SIZE];

		const string get_address();
		t_setup setup();
		
	public:
		Server(u_int32_t address, u_int16_t port);
		~Server();
};

/******************************************************************************/

#endif /* XXX */