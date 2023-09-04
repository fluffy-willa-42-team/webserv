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

		u_int32_t address;
		u_int16_t port;

		int32_t server_fd;
		int32_t connection_fd;

		bool is_running;

		sockaddr_in address_struct;
		char	buffer[BUFFER_SIZE];


	public:
		Server();
		Server(u_int32_t address, u_int16_t port);
		~Server();
		const Server& operator=(const Server& other);

		t_setup setup();
		void start();
		void stop();

		const string get_address();
		bool is_it_running();
		void print_waiting_msg();
};

/******************************************************************************/

#endif /* XXX */