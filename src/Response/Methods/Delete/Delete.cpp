#include <Delete.hpp>

Delete::Delete(const Request& req) : Response(req){
	cout << PURPLE << "Constructing a DELETE method" << RESET << endl;
}

string Delete::toString() const {
	stringstream res;
	res << "HTTP/1.1" << " " << "[Status code]" << " " << "[Status Message]" << endl
		<< "Date: "				<< "[Date]"				<< endl
		<< "Server: "			<< "[Server name]"		<< endl
		<< "Content-Length: "	<< "[Content Length]"	<< endl
		<< "Content-Type: "		<< "[Content Type]"		<< endl;
	
	if (content)
	res << endl
		<< *content;
	
	return res.str();
}
