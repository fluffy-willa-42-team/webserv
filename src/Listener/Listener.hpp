#ifndef LISTENER_HPP
# define LISTENER_HPP

/******************************************************************************/

#include "webserv.hpp"
#include "Config.hpp"
#include <netinet/in.h>

/******************************************************************************/

# define BUFFER_SIZE 800

typedef struct {
	u_int32_t code;
	int32_t err; // TODO Remove
	string message;
}	t_setup;

/******************************************************************************/

class Listener {
	private:

		u_int16_t port;

		int32_t listener_fd;
		int32_t connection_fd;

		bool is_running;

		Config* config;

		sockaddr_in address_struct;
		char	buffer[BUFFER_SIZE];



	public:
		Listener();
		Listener(u_int16_t port, Config* config);
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

		const Config* get_config();
};

/******************************************************************************/

#endif /* LISTENER_HPP */