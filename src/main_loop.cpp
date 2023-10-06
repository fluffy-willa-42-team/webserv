#include "Listener.hpp"
#include "http.hpp"
#include <list>
#include <unistd.h>
#include "Poll.hpp"

void start(map<int, Listener*>& listeners, bool& loop, const Config& config, const Env& env) {
	// Return if all failed to start
	if (listeners.size() < 1){
		cout << "No Listener Started" << endl;
		return ;
	}
	DEBUG_ << "Start server" << endl;

	//TODO WARN If a server failed it will be destroyed ?
	const int listener_nb = listeners.size();
	std::list<Poll> poll_queue;

	//Store all listener pollfd
	for (map<int, Listener*>::iterator ite = listeners.begin(); ite != listeners.end(); ++ite){
		pollfd tmp;
		// = {ite->second->listener_fd, POLLIN, 0}
		tmp.events = POLLIN;
		tmp.fd     = ite->second->listener_fd;
		tmp.revents= 0;
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
		
		for (std::list<Poll>::iterator ite = poll_queue.begin(); ite != poll_queue.end();) {
			// cout << "poll queue size: " << poll_queue.size() << endl;
			if (!loop && ite == poll_queue.end()) {
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
				// DEBUG_WARN_ << "No new connection, ignoring" << endl;
				++ite;
				continue ;
			}
			if (!(ite->poll.revents & POLLIN) && !(ite->poll.revents & POLLOUT)) {
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

				pollfd new_pollfd;
				new_pollfd.events = POLLIN;
				new_pollfd.fd     = connection_fd;
				new_pollfd.revents= 0;
				//TODO handle error
				poll_queue.push_back(Poll(READ, new_pollfd, ""));
				++ite;
				continue ;
			}

			if (type == READ) {

				DEBUG_ << "Read poll id: " << ite->id << endl;
				//TODO handle error
				ite->response = http(poll.fd, config, env);
				ite->type = WRITE;
				ite->poll.events = POLLOUT;
				++ite;
				continue;
			}

			if (type == WRITE) {
				DEBUG_ << "Write poll id: " << ite->id << endl;
				DEBUG_ << "Response: " << endl << ite->response << endl;
				//TODO handle error
				if (send(poll.fd, ite->response.c_str(), ite->response.length(), 0) < 0) {
					DEBUG_WARN_ << "Failed to write to socket" << endl;
				}
				if (close(poll.fd) < 0) {
					DEBUG_WARN_ << "Failed to close socket" << endl;
				}
				DEBUG_INFO_ << "End of connection" << endl;
				ite = poll_queue.erase(ite);
				continue;
			}
		}
	}
}
