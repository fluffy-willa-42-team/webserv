#include "Listener.hpp"
#include "http.hpp"
#include <unistd.h>

void start(map<int, Listener*>& listeners, bool& loop, const Config& config){
	// Return if all failed to start
	if (listeners.size() < 1){
		cout << "No Listener Started" << endl;
		return ;
	}
	DEBUG_ << "Start server" << endl;
	// Execute try_exec of all server at each execution.
	/*

	| 1 | 2 | 3 |            | 1 | 2 | 3 |            | 1 | 2 | 3 |
	|---|---|---|     =>     |---|---|---|     =>     |---|---|---|
	| x |   |   |            |   | x |   |            |   |   | x |
      ^															|
	  |															|
      O---------------------------------------------------------O
	
	*/
	while (loop){
		for (map<int, Listener*>::iterator ite = listeners.begin(); ite != listeners.end();){
			// Check new connection
			const int poll_ret = poll(&(ite->second->wpoll), 1, 0);

			if(poll_ret == 0){
				++ite;
				continue ;
			}
			if (poll_ret < 0){
				DEBUG_WARN_ << "Failed to poll, ignoring" << std::endl;
				++ite;
				continue ;
			}
			if (!(ite->second->wpoll.revents & POLLIN)){
				DEBUG_WARN_ << "No new connection (revents: " << ite->second->wpoll.revents << "), ignoring" << std::endl;
				++ite;
				continue ;
			}
			DEBUG_ << "New connection" << endl;
			DEBUG_ << "Listener fd: " << ite->second->listener_fd << endl;
		
			// Accept new connection
			ite->second->connection_fd = accept(ite->second->listener_fd, NULL, NULL);
			if (ite->second->connection_fd < 0){
				DEBUG_WARN_ << "Failed to accept new connection, ignoring" << std::endl;
				++ite;
				continue ;
			}
			DEBUG_ << "Connection fd: " << ite->second->connection_fd << endl;
			DEBUG_ << "There is data to pull ? " << (ite->second->wpoll.revents & POLLIN) << endl;
			DEBUG_ << "There is data to push ? " << (ite->second->wpoll.revents & POLLOUT) << endl;
			DEBUG_ << "There is an error ? " << (ite->second->wpoll.revents & POLLERR) << endl;
			DEBUG_ << "There is a hangup ? " << (ite->second->wpoll.revents & POLLHUP) << endl;
			DEBUG_ << "There is a priority event ? " << (ite->second->wpoll.revents & POLLPRI) << endl;
			DEBUG_ << "There is a invalid request ? " << (ite->second->wpoll.revents & POLLNVAL) << endl;

			// TODO REMOVE
			string buff = ite->second->read_buff();
			DEBUG_ << "buff: " << buff << endl;

			// TODO @willaCS how we need to handle error ?
			http(buff, *(ite->second), config);

		}
	}

}
