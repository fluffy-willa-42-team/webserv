#include "Listener.hpp"

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


			// Accept new connection
			ite->second->connection_fd = accept(ite->second->listener_fd, NULL, NULL);
			//TODO WIP
		}
	}
	for (map<int, Listener*>::iterator ite = listeners.begin(); ite != listeners.end(); ite++){
		// TODO
		// ite->second.stop();
		delete ite->second;
	}
}
