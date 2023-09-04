#include "Server.hpp"

#include <unistd.h>

Server::Server(u_int32_t address, u_int16_t port)
: address(address), port(port), server_fd(-1), connection_fd(-1)
{
	memset(buffer, 0, sizeof(address_struct));
	memset(buffer, 0, BUFFER_SIZE);
	address_struct.sin_addr.s_addr = address;
	address_struct.sin_port = port;

	cout << CYAN << "Starting Server      : " << this->get_address() << RESET << endl;

	t_setup res = setup();
	if (res.code != 0){
		cout << res.code << " " << res.err << " " << res.message << endl;
	}
}

Server::~Server(){
	close(server_fd);
	close(connection_fd);
	cout << CYAN << "Shutting down Server : " << this->get_address() << RESET << endl;
}
