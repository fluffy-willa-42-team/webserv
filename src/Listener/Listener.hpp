#ifndef SERVER_HPP
# define SERVER_HPP

/******************************************************************************/

#include "webserv.hpp"
#include <netinet/in.h>

/******************************************************************************/

# define BUFFER_SIZE 800

typedef struct {
	u_int32_t code;
	int32_t err;
	string message;
}	t_setup;

typedef enum {
	S_CONTINUE,
	S_STOP,
}	e_status;

/******************************************************************************/

class Listener {
	private:

		u_int16_t port;

		int32_t listener_fd;
		int32_t connection_fd;

		bool is_running;

		sockaddr_in address_struct;
		char	buffer[BUFFER_SIZE];


	public:
		Listener();
		Listener(u_int16_t port);
		~Listener();
		const Listener& operator=(const Listener& other);

		t_setup setup();
		e_status try_exec();
		void stop();
		string read_buff();
		void exec();

		const string get_address();
		bool is_it_running();
		void print_waiting_msg();
};

/******************************************************************************/

#endif /* SERVER_HPP */