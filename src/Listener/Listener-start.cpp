#include "Listener.hpp"

#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <iomanip>

#include <netinet/in.h>

#include "debug.hpp"

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
	
	if (setsockopt(listener_fd, SOL_SOCKET, SO_REUSEADDR, &flags, sizeof(int)) < 0){
		return ret(4, "failed to set socket options");
	}

	// bind socket to a port
	if (bind(listener_fd, ((sockaddr *)&address_struct), sizeof(sockaddr_in)) < 0){
		return ret(5, "failed to bind socket server to port");
	}

	// listens to port for new TCP connection
	if (listen(listener_fd, 256) < 0){
		return ret(6, "failed to listen to socket server");
	}
	
	// Setup pollfd
	wpoll[0].fd = listener_fd;
	wpoll[0].events = POLLIN;

	int poll_check = poll(wpoll, 1, 0);

	if (poll_check < 0){
		return ret(7, "failed to poll");
	}

	DEBUG_() << "poll() returned " << poll_check << " events";

	cout << CYAN << "Listening on         : " << get_address() << RESET << endl;
	is_running = true;
	print_waiting_msg();

	return ret(0, "success");
}





e_status Listener::try_exec(const Config& config){
	if (!is_running){
		return S_STOP;
	}

	//TODO use poll() to check if there is a new connection instead of accept() blocking
	// get new connection (non-blocking due to setup)

	int ret = poll(wpoll, 1, 0);

	// check if poll failed
	if (ret < 0){
		DEBUG_WARN_() << "Failed to poll, ignoring";
		return S_CONTINUE;
	}

	if (ret == 0){
		return S_CONTINUE;
	}

	if (wpoll[0].revents & POLLIN){
		connection_fd = accept(listener_fd, NULL, NULL);
	}

	// check if error in accept after having recieved a connection
	if (connection_fd < 0)
	{
		DEBUG_WARN_() << "Failed to accept connection, ignoring";
		return S_CONTINUE;
	}

	// retrieve the file descriptor flags
	int flags = fcntl(listener_fd, F_GETFL, 0);
	if (flags < 0){
		DEBUG_WARN_() << "Failed to retrieve the flags for server file descriptor, ignoring";
		return S_CONTINUE;
	}
	
	// verify the file descriptor has the right O_NONBLOCK flag
	flags |= O_NONBLOCK;
	if (fcntl(listener_fd, F_SETFL, flags) < 0){
		DEBUG_WARN_() << "Failed to retrieve the flags for server file descriptor, ignoring";
		return S_CONTINUE;
	}

	exec(config);
	print_waiting_msg();
	return S_CONTINUE;
}





void Listener::stop(){
	if (!is_running)
		return ;
	is_running = false;
	cout << CYAN << "Shutting down Listener : " << this->get_address() << RESET << endl;
}
