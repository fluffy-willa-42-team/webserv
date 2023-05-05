#include "Request.hpp"
#include "Server.hpp"

int start_test();

int main(){
	// start_test();

	Address add("127.0.0.1", "8080");
	cout << "Listening on " << add << endl;

	Server test(0x7f000001, 80);
	return 0;
}