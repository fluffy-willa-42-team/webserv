#include "Listener.hpp"
#include "http.hpp"
#include <list>
#include <unistd.h>
#include "Poll.hpp"
#include "response.hpp"



void start(map<int, Listener*>& listeners, bool& loop, const Config& config, const Env& env) {
	// Return if all failed to start
	if (listeners.size() < 1){
		cout << "No Listener Started" << endl;
		return ;
	}
	DEBUG_ << "Start server" << endl;

	std::list<Poll> poll_queue;

	//Store all listener pollfd
	for (map<int, Listener*>::iterator ite = listeners.begin(); ite != listeners.end(); ++ite){
		pollfd tmp;
		tmp.events = POLLIN;
		tmp.fd     = ite->second->listener_fd;
		tmp.revents= 0;
		poll_queue.push_back(Poll(LISTENER, tmp));
	}

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
			if(ite->type == LISTENER && poll_ret == 0) {
				// DEBUG_WARN_ << "No new connection, ignoring" << endl;
				++ite;
				continue ;
			}
			if (!(ite->poll.revents & POLLIN) && !(ite->poll.revents & POLLOUT)) {
				DEBUG_WARN_ << "No new connection poll id: " << ite->id << " (revents: " << ite->poll.revents << "), ignoring" << endl;
				++ite;
				continue ;
			}

			if (!loop) {
				DEBUG_INFO_ << "Loop stopped just before reading request!" << endl;
				DEBUG_INFO_ << "Try to response to all the request in the queue." << endl;
				//TODO clear the queue
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
				poll_queue.push_back(Poll(READ_HEAD, new_pollfd));
				++ite;
				continue ;
			}

			if (type == READ_HEAD) {
				DEBUG_ << "Read head poll id: " << ite->id << endl;
				// Read header by BUFFER_SIZE until reach the header end sequence
				try {
					read_header(*ite);
				}
				catch(const std::exception& e) {
					DEBUG_WARN_ << "Read header failed, ignoring" << endl;
					ite->type = WRITE;
					ite->poll.events = POLLOUT;
					std::cerr << e.what() << endl;
					// Respond directly to the request
					// ++ite;
					continue;
				}

				// Check if the read_header is complete
				if (ite->type != READ_BODY) {
					// Continue to read the same request until all the header is read.
					// ++ite;
					continue;
				}

				// Parse the header
				try {
					parse_header(config, ite->req);
				}
				catch(const std::exception& e) {
					DEBUG_WARN_ << "Pars header failed, ignoring" << endl;
					ite->type = WRITE;
					ite->poll.events = POLLOUT;
					std::cerr << e.what() << endl;
					// Respond directly to the request
					// ++ite;
					continue;
				}
				// If there is no body skip reading body
				const string & method = ite->req.method;
				ite->type = (method != "POST" && method != "DELETE") ? WRITE : READ_BODY;
				if (ite->type == READ_BODY) {
					if (!map_has_key(ite->req.headers, string(HEADER_CONTENT_LENGTH))) {
						DEBUG_WARN_ << "Request dont have a content length for the body!, ignoring" << endl;
						ite->type = WRITE;
						ite->req.response = error(400, "The Header dont have a content length for the body!");
						// Respond directly to the request
						// ++ite;
						continue;
					}

					ite->req.content_length = stringToNumber(ite->req.headers[HEADER_CONTENT_LENGTH]);
					if (ite->req.serv.has_max_body_size_been_set) {
						if (ite->req.serv.max_body_size < (u_int32_t) ite->req.body.size()) {
							DEBUG_ << "Body exeed max_body_size!" << endl;
							ite->req.response = error_serv(ite->req.serv, 413);
							// Respond directly to the request
							// ++ite;
							continue;
						}
					}
				}
				// Continue to read the same request
				// ++ite;
				continue;
			}

			if (type == READ_BODY) {
				try {
					read_body(*ite);
				}
				catch(const std::exception& e) {
					DEBUG_WARN_ << "Read Body failed, ignoring" << endl;
					ite->type = WRITE;
					std::cerr << e.what() << endl;
					// Respond directly to the request
					// ++ite;
				}
				continue;
			}

			if (type == EXE_CGI) {
				try
				{
					execute_request(env, ite->req);
				}
				catch(const std::exception& e)
				{
					DEBUG_WARN_ << "Execute CGI failed, ignoring" << endl;
					std::cerr << e.what() << endl;
				}
				ite->type = WRITE;
				// Respond directly to the request
				// ++ite;
				continue;
			}

			if (type == WRITE) {
				DEBUG_ << "Write poll id: " << ite->id << endl;
				if (send(poll.fd, ite->req.response.c_str(), ite->req.response.length(), 0) < 0) {
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
