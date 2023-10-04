#include "Listener.hpp"
#include "http.hpp"
#include <vector>
#include <unistd.h>
#include "Poll.hpp"

void start(map<int, Listener*>& listeners, bool& loop, const Config& config, const Env& env) {
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
	vector<Poll> poll_queue;

	//Store all listener pollfd
	for (map<int, Listener*>::iterator ite = listeners.begin(); ite != listeners.end(); ++ite){
		const pollfd tmp = {ite->second->listener_fd, POLLIN, 0};
		poll_queue.push_back(Poll(LISTENER, tmp, ""));
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

		for (vector<Poll>::iterator ite = poll_queue.begin(); ite != poll_queue.end();) {
			if (!loop) {
				break;
			}

			const int poll_ret = poll(&(ite->poll), 1, 0);

			if (poll_ret < 0) {
				DEBUG_WARN_ << "Failed to poll id: " << ite->id << ", ignoring" << endl;
				DEBUG_WARN_ << "Error: " << strerror(errno) << endl;
				++ite;
				continue ;
			}
			if(poll_ret == 0){
				++ite;
				// DEBUG_WARN_ << "No new connection, ignoring" << endl;
				continue ;
			}
			if (!(ite->poll.revents & POLLIN)){
				DEBUG_WARN_ << "No new connection poll id: " << ite->id << " (revents: " << ite->poll.revents << "), ignoring" << endl;
				++ite;
				continue ;
			}


			if (!loop) {// TODO check on macos if this fix the freez with ctrl+c
				DEBUG_INFO_ << "Loop stoped just befor reading request!" << endl;
				return ;
			}

			const PollType type = ite->type;
			const pollfd poll = ite->poll;

			if (type == LISTENER) {

				DEBUG_ << "Connection poll id: " << ite->id << endl;
				// Accept new connection
				const int connection_fd = accept(poll.fd, NULL, NULL);
				if (connection_fd < 0){
					DEBUG_WARN_ << "Failed to accept new connection, ignoring" << endl;
					++ite;
					continue ;
				}

				DEBUG_ << "New connection accepted and stored: " << connection_fd << endl;

				pollfd new_pollfd = {connection_fd, POLLIN, 0};
				poll_queue.push_back(Poll(READ, new_pollfd, ""));
				ite ++;
				continue ;
			}

			if (type == READ) {

				DEBUG_ << "Read poll id: " << ite->id << endl;
				ite->response = http(poll.fd, config, env);
				ite->type = WRITE;
				ite++;
				continue;
			}

			if (type == WRITE) {
				DEBUG_ << "Write poll id: " << ite->id << endl;
				if (send(poll.fd, ite->response.c_str(), ite->response.length(), 0) < 0) {
					DEBUG_WARN_ << "Failed to write to socket" << endl;
				}
				if (close(poll.fd) < 0) {
					DEBUG_WARN_ << "Failed to close socket" << endl;
				}
				DEBUG_INFO_ << "End of connection" << endl;
				ite++;
				continue;
			}

			//TODO Check if we proprely use poll()
			// https://beej.us/guide/bgnet/html/split/slightly-advanced-techniques.html#blocking
			// Check new connection


		// 	DEBUG_ << "Listener fd: " << ite->fd << endl;
		
		// 	// Accept new connection
		// 	const int connection_fd = accept(ite->fd, NULL, NULL);
		// 	if (connection_fd < 0){
		// 		DEBUG_WARN_ << "Failed to accept new connection, ignoring" << endl;
		// 		++ite;
		// 		continue ;
		// 	}

		// 	DEBUG_ << "New connection accepted and stored: " << connection_fd << endl;

		// 	pollfd new_pollfd = {connection_fd, POLLIN, 0};
		// 	pollfds.push_back(new_pollfd);
		// 	ite ++;
		// }
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
}
