#include <Get.hpp>

Get::Get(const Request& req) : Response(req){
	cout << PURPLE << "Constructing a GET method" << RESET << endl;
}

string Get::toString() const {
	stringstream res;
	res << "HTTP/1.1" << " " << "[Status code]" << " " << "[Status Message]" << endl
		<< "Date: " << "[Date]" << endl
		<< "Server: " << "[Server name]" << endl
		<< "Content-Length: " << "[Content Length]" << endl
		<< "Content-Type: [Content Type]" << endl;
	
	if (content)
	res << endl
		<< *content;
	
	return res.str();
}
