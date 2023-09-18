#include "Listener.hpp"
#include <csignal>

void init();

static map<int, Listener> servers;
static bool loop = true;

void setup(map<int, Listener>& servers);
void start(map<int, Listener>& servers, bool& loop);
void shutdown(int signal){
	(void) signal;
	loop = false;
	cout << endl;
	for (map<int, Listener>::iterator ite = servers.begin(); ite != servers.end(); ite++){
		ite->second.stop();
	}
}

int main(int argc, char* argv[]){
	init();

	// Parse config
	if (argc > 2){
		cerr << "Error: Invalid Number of arguments" << endl;
		cerr << "./webserv [?filepath_to_config]" << endl;
		return 1;
	}

	string config_path = argc == 2 ? argv[1] : DEFAULT_CONFIG_PATH;
	// Config config(config_path);

	// for (vector<u_int32_t>::iterator ite = config.ports.begin(); ite = config.ports.end(); ite++){
	// 	servers[port] = Listener(port)
	// }
	servers[8001] = Listener(8001);
	servers[8002] = Listener(8002);
	servers[8003] = Listener(8003);

	std::signal(SIGINT, &shutdown);
	setup(servers);
	start(servers, loop);
}
