#include "webserv.hpp"
#include "Server.hpp"

// map<int, Server> servers;

void webserv(){
	Server(0x0605010A, 456);
	// Server(0x0705010A, 456);
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
