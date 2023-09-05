#include "webserv.hpp"
#include "Server.hpp"
#include <csignal>

void init_error_map();

bool loop = true;
map<int, Server> servers;

void start(){
	// Setup every server and delete all that fail setup
	for (map<int, Server>::iterator ite = servers.begin(); ite != servers.end();){
		t_setup res = ite->second.setup();
		if (res.code != 0){
			std::map<int, Server>::iterator temp = ite;
			ite++;
			servers.erase(temp);
		}
		else {
			ite++;
		}
	}
	// Return if all failed to start
	if (servers.size() < 1){
		return ;
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
		for (map<int, Server>::iterator ite = servers.begin(); ite != servers.end();){
			e_status status = ite->second.try_exec();
			if (status == S_STOP){
				ite->second.stop();
				std::map<int, Server>::iterator temp = ite;
				ite++;
				servers.erase(temp);
			}
			else {
				ite++;
			}
		}
	}
}

void shutdown(int signal){
	(void) signal;
	loop = false;
	cout << endl;
	for (map<int, Server>::iterator ite = servers.begin(); ite != servers.end(); ite++){
		ite->second.stop();
	}
	loop = false;
}

void webserv(){
	servers[8001] = Server(0, 8001);
	servers[8002] = Server(0, 8002);
	servers[8003] = Server(0, 8003);

	std::signal(SIGINT, &shutdown);
	start();
}

int main(){
	try
	{
		init_error_map();
		// webserv();
	}
	catch(const exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}
