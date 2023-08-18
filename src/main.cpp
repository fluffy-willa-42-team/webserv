#include "Request.hpp"
#include "Server.hpp"
#include "webserv.hpp"

#include <csignal>

bool loop = true;
map<int, Server> servers;

int start_test();
void test_req();

void start(){
	for (map<int, Server>::iterator ite = servers.begin(); ite != servers.end(); ite++){
		try {
			ite->second.setup();
			ite->second.print_waiting_msg();
		}
		catch(const std::exception& e) {
			std::cerr << RED << e.what() << RESET << endl;
		}
		
	}
	while (loop){
		for (map<int, Server>::iterator ite = servers.begin(); ite != servers.end(); ite++){
			if (ite->second.is_it_running())
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

void webserv(){
	// start_test();
	// test_req();

	//TODO load config file

	//TODO setup Server with config
	servers[8001] = Server(Address("0.0.0.0", "8001"));
	servers[8002] = Server(Address("0.0.0.0", "8002"));
	servers[8003] = Server(Address("0.0.0.0", "8003"));

	std::signal(SIGINT, &shutdown);
	start();
}

int main(){
	try
	{
		webserv();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}