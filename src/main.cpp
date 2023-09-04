#include "webserv.hpp"
#include "Server.hpp"

// map<int, Server> servers;

void webserv(){
	cout << sizeof(sockaddr_in) << endl;
	// Server test(0x0605010A, 1456);
	Server test(0, 1456);
	// test.setup();
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
