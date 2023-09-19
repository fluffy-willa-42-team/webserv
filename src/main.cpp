#include "Listener.hpp"
#include "Config.hpp"
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
		cerr << RED << "Error: Invalid Number of arguments" << RESET << endl;
		cerr << RED << "./webserv [?filepath_to_config]" << RESET << endl;
		return 1;
	}

	string config_path = argc == 2 ? argv[1] : DEFAULT_CONFIG_PATH;
	Config config(config_path);
	if (!config.valid){
		cerr << RED << "Error: Config is Invalid" << RESET << endl;
		return 1;
	}
	
	for (vector<u_int32_t>::iterator ite = config.ports.begin(); ite != config.ports.end(); ite++){
		listeners[*ite] = Listener(*ite);
	}

	std::signal(SIGINT, &shutdown);
	setup(listeners);
	start(listeners, loop);
}
