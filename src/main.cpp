#include "Request.hpp"
#include "Server.hpp"
#include "using.hpp"

#include <csignal>

map<int, Server> servers;

int start_test();

void shutdown(int signal){
	(void) signal;
	for (map<int, Server>::iterator ite = servers.begin(); ite != servers.end(); ite++){
		Server serv = ite->second;
		serv.stop();
		cout << "Serv Stopped" << endl;
	}
}

int main(){
	// start_test();

	Address add("0.0.0.0", "8080");
	
	std::signal(SIGINT, &shutdown);

	servers[8080] = Server(add);
	servers[8080].start();
	return 0;
}