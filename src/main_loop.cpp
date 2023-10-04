#include "Listener.hpp"
#include "http.hpp"
#include <vector>
#include <unistd.h>

void start(map<int, Listener*>& listeners, bool& loop, const Config& config, const Env& env){
	// Return if all failed to start
	if (listeners.size() < 1){
		cout << "No Listener Started" << endl;
		return ;
	}
	DEBUG_ << "Start server" << endl;

	//TODO Create array of pollfd and fill it with all listener_fd and connection_fd


	//TODO REWORK
	//TODO REWORK
	//TODO REWORK Create a new class that will handle all the pollfd for accept, read and write
	//TODO REWORK Each class will have a type [LISTENER, CONNECTION, READ, WRITE]
	//TODO REWORK Each class will store a pollfd and the data needed for the type (aka connection_fd for connection, http response for write, etc...)
	//TODO REWORK
	//TODO REWORK


	//TODO WARN If a server faild it weel be destroy ?
	const int listener_nb = listeners.size();
	vector<pollfd> pollfds;
	for (map<int, Listener*>::iterator ite = listeners.begin(); ite != listeners.end(); ++ite){
		pollfds.push_back(ite->second->wpoll);
	}

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

		const int poll_ret = poll(pollfds.data(), 1, 0);
		for (vector<pollfd>::iterator ite = pollfds.begin(); ite != pollfds.end();) {
			if (!loop) {
				break;
			}

			if (ite - pollfds.begin() > listener_nb) {
				if (!loop) {// TODO check on macos if this fix the freez with ctrl+c
					DEBUG_INFO_ << "Loop stoped just befor reading http request!" << endl;
					return ;
				}
				string response = http(ite->fd, config, env);

				if (send(ite->second->connection_fd, response.c_str(), response.length(), 0) < 0) {
					DEBUG_WARN_ << "Failed to write to socket" << endl;
				}
				if (close(ite->second->connection_fd) < 0) {
					DEBUG_WARN_ << "Failed to close socket" << endl;
				}
				DEBUG_INFO_ << "End of connection" << endl;
			}
			//TODO Check if we proprely use poll()
			// https://beej.us/guide/bgnet/html/split/slightly-advanced-techniques.html#blocking
			// Check new connection

			if(poll_ret == 0){
				++ite;
				// DEBUG_WARN_ << "No new connection, ignoring" << endl;
				continue ;
			}
			if (poll_ret < 0){
				DEBUG_WARN_ << "Failed to poll, ignoring" << endl;
				++ite;
				continue ;
			}
			if (!(ite->revents & POLLIN)){
				DEBUG_WARN_ << "No new connection (revents: " << ite->revents << "), ignoring" << endl;
				++ite;
				continue ;
			}
			DEBUG_ << "New connection" << endl;
			DEBUG_ << "Listener fd: " << ite->fd << endl;
		
			// Accept new connection
			const int connection_fd = accept(ite->fd, NULL, NULL);
			if (connection_fd < 0){
				DEBUG_WARN_ << "Failed to accept new connection, ignoring" << endl;
				++ite;
				continue ;
			}

			DEBUG_ << "New connection accepted and stored: " << connection_fd << endl;

			pollfd new_pollfd = {connection_fd, POLLIN, 0};
			pollfds.push_back(new_pollfd);
			ite ++;
		}
	// 	for (map<int, Listener*>::iterator ite = listeners.begin(); ite != listeners.end();){
	// 		if (!loop) {
	// 			break;
	// 		}
	// 		//TODO Check if we proprely use poll()
	// 		// https://beej.us/guide/bgnet/html/split/slightly-advanced-techniques.html#blocking
	// 		// Check new connection
	// 		const int poll_ret = poll(&(ite->second->wpoll), 1, 0);

	// 		if(poll_ret == 0){
	// 			++ite;
	// 			// DEBUG_WARN_ << "No new connection, ignoring" << endl;
	// 			continue ;
	// 		}
	// 		if (poll_ret < 0){
	// 			DEBUG_WARN_ << "Failed to poll, ignoring" << endl;
	// 			++ite;
	// 			continue ;
	// 		}
	// 		if (!(ite->second->wpoll.revents & POLLIN)){
	// 			DEBUG_WARN_ << "No new connection (revents: " << ite->second->wpoll.revents << "), ignoring" << endl;
	// 			++ite;
	// 			continue ;
	// 		}
	// 		DEBUG_ << "New connection" << endl;
	// 		DEBUG_ << "Listener fd: " << ite->second->listener_fd << endl;
		
	// 		// Accept new connection
	// 		ite->second->connection_fd = accept(ite->second->listener_fd, NULL, NULL);
	// 		if (ite->second->connection_fd < 0){
	// 			DEBUG_WARN_ << "Failed to accept new connection, ignoring" << endl;
	// 			++ite;
	// 			continue ;
	// 		}
	// 		// DEBUG_ << "Connection fd: " << ite->second->connection_fd << endl;
	// 		// DEBUG_ << "There is data to pull ? " << (ite->second->wpoll.revents & POLLIN) << endl;
	// 		// DEBUG_ << "There is data to push ? " << (ite->second->wpoll.revents & POLLOUT) << endl;
	// 		// DEBUG_ << "There is an error ? " << (ite->second->wpoll.revents & POLLERR) << endl;
	// 		// DEBUG_ << "There is a hangup ? " << (ite->second->wpoll.revents & POLLHUP) << endl;
	// 		// DEBUG_ << "There is a priority event ? " << (ite->second->wpoll.revents & POLLPRI) << endl;
	// 		// DEBUG_ << "There is a invalid request ? " << (ite->second->wpoll.revents & POLLNVAL) << endl;

	// 		if (!loop) {// TODO check on macos if this fix the freez with ctrl+c
	// 			DEBUG_INFO_ << "Loop stoped just befor reading http request!" << endl;
	// 			return ;
	// 		}
	// 		string response = http(*(ite->second), config, env);

	// 		if (send(ite->second->connection_fd, response.c_str(), response.length(), 0) < 0) {
	// 			DEBUG_WARN_ << "Failed to write to socket" << endl;
	// 		}
	// 		if (close(ite->second->connection_fd) < 0) {
	// 			DEBUG_WARN_ << "Failed to close socket" << endl;
	// 		}
	// 		DEBUG_INFO_ << "End of connection" << endl;
	// 	}
	}

}
