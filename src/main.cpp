#include "Listener.hpp"
#include <csignal>

void init();

static map<int, Listener> listeners;
static bool loop = true;

void setup(map<int, Listener>& listeners);
void start(map<int, Listener>& listeners, bool& loop);
void shutdown(int signal){
	(void) signal;
	loop = false;
	cout << endl;
	for (map<int, Listener>::iterator ite = listeners.begin(); ite != listeners.end(); ite++){
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
	// 	listeners[port] = Listener(port)
	// }
	listeners[8001] = Listener(8001);
	listeners[8002] = Listener(8002);
	listeners[8003] = Listener(8003);

	std::signal(SIGINT, &shutdown);
	setup(listeners);
	start(listeners, loop);
}
