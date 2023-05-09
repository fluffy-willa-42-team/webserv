#include "Request.hpp"
#include "Server.hpp"
#include "using.hpp"

#include <csignal>

bool loop = true;
map<int, Server> servers;

int start_test();

void start(){
	for (map<int, Server>::iterator ite = servers.begin(); ite != servers.end(); ite++){
		ite->second.start_parallel();
	}
}

void shutdown(int signal){
	(void) signal;
	for (map<int, Server>::iterator ite = servers.begin(); ite != servers.end(); ite++){
		ite->second.stop();
	}
	loop = false;
}

int main(){
	// start_test();

	std::signal(SIGINT, &shutdown);

	servers[8001] = Server(Address("0.0.0.0", "8001"));
	servers[8002] = Server(Address("0.0.0.0", "8002"));
	servers[8003] = Server(Address("0.0.0.0", "8003"));

	start();

	while (loop);
	
	return 0;
}