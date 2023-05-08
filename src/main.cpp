#include "Request.hpp"
#include "Server.hpp"
#include "using.hpp"

#include <csignal>

map<int, Server *> servers;

int start_test();

void testx(int x){
	cout << "HEllo: " << x << endl;
	servers[8080]->stop(); 
}

int main(){
	// start_test();


	Address add("0.0.0.0", "8080");
	
	Server test(add);
	servers[8080] = &test;
	
	std::signal(SIGINT, &testx);

	servers[8080]->start(); 


	return 0;
}