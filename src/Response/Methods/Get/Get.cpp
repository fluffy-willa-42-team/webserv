#include <Get.hpp>

Get::Get(const Request& req) : Response(req){
	cout << PURPLE << "Constructing a GET method" << RESET << endl;
}

string Get::toString() const {
	stringstream res;
	res << "GET " << request;
	return res.str();
}