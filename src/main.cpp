#include "webserv.hpp"
#include "Server.hpp"

bool loop = true;
map<int, Server> servers;

void start(){
	for (map<int, Server>::iterator ite = servers.begin(); ite != servers.end(); ite++){
		t_setup res = ite->second.setup();
		if (res.code != 0){
			cout << res.code << " " << res.err << " " << res.message << endl;
			servers.erase(ite);
		}
		ite->second.start();
	}
	// while (loop);
}

void shutdown(int signal){
	(void) signal;
	for (map<int, Server>::iterator ite = servers.begin(); ite != servers.end(); ite++){
		ite->second.stop();
	}
	loop = false;
}

void webserv(){
	servers[8001] = Server(0, 8001);

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
