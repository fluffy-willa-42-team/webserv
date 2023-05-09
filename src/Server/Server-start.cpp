#include "Server.hpp"
#include "Request.hpp"

#include <errno.h>

/* ************************************************************************** */

/**
 * @brief Will start a standalone server that is blocking. This is not meant to
 * be used for multiple server.
 */
void Server::start(){
	setup();

	print_waiting_msg();
	while(is_running)
	{
		e_try res = try_connection();

		if (res == NO_CONNECTION)
			continue ;
		if (res == END_OF_RUNTIME)
			return ;		
		
		print_waiting_msg();
	}
}



e_try Server::try_connection(){
	connection_fd = accept(server_fd, NULL, NULL);	// get new connection (non-blocking due to setup)
	if (connection_fd < 0 && errno == EWOULDBLOCK)	// check if there is a new connection
		return (NO_CONNECTION);
	if (connection_fd < 0){		// check if error in accept after having recieved a connection
		if (is_running){
			cout << is_running << " " << connection_fd << endl;
			throw InternalError();
		}
		return (END_OF_RUNTIME);
	}
	
	exec();
	print_waiting_msg();
	return (SUCCESS);
}
