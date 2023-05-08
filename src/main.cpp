#include "Request.hpp"
#include "Server.hpp"

int start_test();

int main(){
	// start_test();

	Address add("0.0.0.0", "8080");
	Server test(add);
	test.start();


	return 0;
}