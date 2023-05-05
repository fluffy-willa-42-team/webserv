#include "Request.hpp"
#include "Server.hpp"

int start_test();

int main(){
	// start_test();

	Address add("127.10.28.1", "7080");
	cout << "Listening on " << add << endl;

	Server test(0x7f000001, 80);
	return 0;
}