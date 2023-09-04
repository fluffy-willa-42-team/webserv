#include "Server.hpp"

#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <iomanip>

#include <netinet/in.h>

t_setup ret(u_int32_t code, const string& message){
	t_setup res;
	res.code = code;
	res.err = errno;
	res.message = message;
	return res;
}

t_setup Server::setup(){
	// Create Socket file descriptor for server
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0){
		return ret(1, "failed to bind socket");
	}
	
	// verify the file descriptor has the right flags
	int flags = fcntl(server_fd, F_GETFL, 0);
    if (flags < 0){
		return ret(2, "failed to retrieve the flags for server file descriptor");
	}
	flags |= O_NONBLOCK;
    if (fcntl(server_fd, F_SETFL, flags) < 0){
		return ret(3, "failed to retrieve the flags for server file descriptor");
	}
	
	if (bind(server_fd, ((sockaddr *)&address_struct), sizeof(sockaddr_in)) < 0){
		return ret(4, "failed to bind socket server to port");
	}

	if (listen(server_fd, 256)){
		return ret(5, "failed to listen to socket server");
	}
	
	cout << CYAN << "Listening on         : " << get_address() << RESET << endl;
	return ret(0, "success");
}

