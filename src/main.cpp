#include "Request.hpp"
#include "Server.hpp"
#include "using.hpp"

#include <csignal>

bool loop = true;
map<int, Server> servers;

int start_test();

void start(){
	for (map<int, Server>::iterator ite = servers.begin(); ite != servers.end(); ite++){
		try {
			ite->second.setup();
		}
		catch(const std::exception& e) {
			std::cerr << RED << e.what() << RESET << endl;
		}
		
	}
	while (loop){
		for (map<int, Server>::iterator ite = servers.begin(); ite != servers.end(); ite++){
			ite->second.try_connection();
		}
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

	servers[8001] = Server(Address("0.0.0.0", "8001"));
	servers[8002] = Server(Address("0.0.0.0", "8002"));
	servers[8003] = Server(Address("0.0.0.0", "8003"));

	std::signal(SIGINT, &shutdown);
	start();
	
	return 0;
}