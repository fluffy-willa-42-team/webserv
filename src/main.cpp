#include "webserv.hpp"
#include "Server.hpp"
#include <csignal>

bool loop = true;
map<int, Server> servers;

void start(){
	// Setup every server and delete all that fail setup
	for (map<int, Server>::iterator ite = servers.begin(); ite != servers.end(); ite++){
		t_setup res = ite->second.setup();
		if (res.code != 0){
			cout << res.code << " " << res.err << " " << res.message << endl;
			servers.erase(ite);
		}
	}
	// Return if all failed to start
	if (servers.size() < 1){
		return ;
	}
	// Execute start_parallel of all server at each execution.
	/*

	| 1 | 2 | 3 |            | 1 | 2 | 3 |            | 1 | 2 | 3 |
	|---|---|---|     =>     |---|---|---|     =>     |---|---|---|
	| x |   |   |            |   | x |   |            |   |   | x |
      ^															|
	  |															|
      O---------------------------------------------------------O
	
	*/
	while (loop){
		for (map<int, Server>::iterator ite = servers.begin(); ite != servers.end(); ite++){
			ite->second.start_parallel();
		}
	}
}

void shutdown(int signal){
	(void) signal;
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
		webserv();
	}
	catch(const exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}
