#include "Listener.hpp"
#include "Config.hpp"
#include <csignal>
#include "debug.hpp"

void init();

static map<int, Listener> listeners;
static bool loop = true;

void setup(map<int, Listener>& listeners);
void start(map<int, Listener>& listeners, bool& loop, const Config& config);
void shutdown(int signal){
	cout << endl;
	DEBUG_ << "SIGINT caught" << endl;
	(void) signal;
	loop = false;
	for (map<int, Listener>::iterator ite = listeners.begin(); ite != listeners.end(); ite++){
		//TODO
		// ite->second.stop();
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
	
	for (vector<Server>::iterator ite = config.servers.begin(); ite != config.servers.end(); ite++){
		DEBUG_INFO_ << "Server: " << ite->host << ":" << ite->port << endl;
		listeners[ite->port] = Listener(ite->host, ite->port);
	}

	std::signal(SIGINT, &shutdown);
	setup(listeners);
	start(listeners, loop, config);
}
