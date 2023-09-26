#include "Listener.hpp"

#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <iomanip>

#include <netinet/in.h>

#include "debug.hpp"


// e_status Listener::try_exec(const Config& config){
// 	if (!is_running){
// 		return S_STOP;
// 	}

// 	//TODO use poll() to check if there is a new connection instead of accept() blocking
// 	// get new connection (non-blocking due to setup)

// 	int ret = poll(wpoll, 1, 0);

// 	// check if poll failed
// 	if (ret < 0){
// 		DEBUG_WARN_ << "Failed to poll, ignoring" << std::endl;
// 		return S_CONTINUE;
// 	}

// 	if (ret == 0){
// 		return S_CONTINUE;
// 	}

// 	if (!(wpoll[0].revents & POLLIN)){
// 		DEBUG_WARN_ << "No new connection (revents: " << wpoll[0].revents << "), ignoring" << std::endl;
// 		return S_CONTINUE;
// 	}

// 	connection_fd = accept(listener_fd, NULL, NULL);
// 	// check if error in accept after having recieved a connection
// 	if (connection_fd < 0)
// 	{
// 		DEBUG_WARN_ << "Failed to accept connection, ignoring" << std::endl;
// 		return S_CONTINUE;
// 	}

// 	// retrieve the file descriptor flags
// 	int flags = fcntl(listener_fd, F_GETFL, 0);
// 	if (flags < 0){
// 		DEBUG_WARN_ << "Failed to retrieve the flags for server file descriptor, ignoring" << std::endl;
// 		return S_CONTINUE;
// 	}
	
// 	// verify the file descriptor has the right O_NONBLOCK flag
// 	flags |= O_NONBLOCK;
// 	if (fcntl(listener_fd, F_SETFL, flags) < 0){
// 		DEBUG_WARN_ << "Failed to retrieve the flags for server file descriptor, ignoring" << std::endl;
// 		return S_CONTINUE;
// 	}

// 	exec(config);
// 	print_waiting_msg();
// 	return S_CONTINUE;
// }





// void Listener::stop(){
// 	if (!is_running)
// 		return ;
// 	is_running = false;
// 	cout << CYAN << "Shutting down Listener : " << this->get_address() << RESET << endl;
// }
