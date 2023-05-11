#include <Get.hpp>

string get_now();

Get::Get(const Request& req) : Response(req){
	cout << PURPLE << "Constructing a GET method" << RESET << endl;
}

string Get::toString() const {
	stringstream res;
	res << PROTOCOL << " " << "[Status code]" << " " << "[Status Message]" << endl
		<< "Date: "				<< get_now()			<< endl
		<< "Server: "			<< "[Server name]"		<< endl;
	
	if (!content)
	res	<< "Content-Length: "	<< 0					<< endl;
	else
	res	<< "Content-Length: "	<< content->length		<< endl
		<< "Content-Type: "		<< content->type		<< endl
		<< endl
		<< *content;
	
	return res.str();
}
