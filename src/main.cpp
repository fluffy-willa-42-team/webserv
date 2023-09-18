#include "Server.hpp"
#include <csignal>

void init();

static map<int, Server> servers;
static bool loop = true;

void setup(map<int, Server>& servers);
void start(map<int, Server>& servers, bool& loop);
void shutdown(int signal){
	(void) signal;
	loop = false;
	cout << endl;
	for (map<int, Server>::iterator ite = servers.begin(); ite != servers.end(); ite++){
		ite->second.stop();
	}
}

int main(){
	init();

	servers[8001] = Server(0, 8001);
	servers[8002] = Server(0, 8002);
	servers[8003] = Server(0, 8003);

	std::signal(SIGINT, &shutdown);
	setup(servers);
	start(servers, loop);
}
