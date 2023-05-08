#include "Request.hpp"
#include "Server.hpp"

int start_test();

int main(){
	// start_test();

	Address add("0.0.0.0", "1000");
	Server test(add);



	return 0;
}