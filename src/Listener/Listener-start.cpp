#include "Listener.hpp"

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





t_setup Listener::setup(){
	// Create Socket file descriptor for server
	listener_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listener_fd < 0){
		return ret(1, "failed to bind socket");
	}
	
	// retrieve the file descriptor flags
	int flags = fcntl(listener_fd, F_GETFL, 0);
    if (flags < 0){
		return ret(2, "failed to retrieve the flags for server file descriptor");
	}
	
	// verify the file descriptor has the right O_NONBLOCK flag
	flags |= O_NONBLOCK;
	if (fcntl(listener_fd, F_SETFL, flags) < 0){
		return ret(3, "failed to retrieve the flags for server file descriptor");
	}
	
	// bind socket to a port
	if (bind(listener_fd, ((sockaddr *)&address_struct), sizeof(sockaddr_in)) < 0){
		return ret(4, "failed to bind socket server to port");
	}

	// listens to port for new TCP connection
	if (listen(listener_fd, 256) < 0){
		return ret(5, "failed to listen to socket server");
	}
	
	cout << CYAN << "Listening on         : " << get_address() << RESET << endl;
	is_running = true;
	print_waiting_msg();

	return ret(0, "success");
}





e_status Listener::try_exec(){
	if (!is_running){
		return S_STOP;
	}

	// get new connection (non-blocking due to setup)
	connection_fd = accept(listener_fd, NULL, NULL);

	// check if there is a new connection
	if (connection_fd < 0 && errno == EWOULDBLOCK){
		return S_CONTINUE;
	}

	// retrieve the file descriptor flags
	int flags = fcntl(listener_fd, F_GETFL, 0);
    if (flags < 0){
		return S_STOP;
	}
	
	// verify the file descriptor has the right O_NONBLOCK flag
	flags |= O_NONBLOCK;
	if (fcntl(listener_fd, F_SETFL, flags) < 0){
		return S_STOP;
	}

	// check if error in accept after having recieved a connection
	if (connection_fd < 0)
	{
		cout << "STOP" << endl;
		return S_STOP;
	}
	exec();
	print_waiting_msg();
	return S_CONTINUE;
}





void Listener::stop(){
	if (!is_running)
		return ;
	is_running = false;
	cout << CYAN << "Shutting down Listener : " << this->get_address() << RESET << endl;
}