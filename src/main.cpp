#include "webserv.hpp"

// map<int, Server> servers;

void webserv(){
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