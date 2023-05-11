#include <Post.hpp>

Post::Post(const Request& req) : Response(req){
	cout << PURPLE << "Constructing a POST method" << RESET << endl;
}

string Post::toString() const {
	stringstream res;
	res << PROTOCOL << " " << "[Status code]" << " " << "[Status Message]" << endl
		<< "Date: "				<< "[Date]"				<< endl
		<< "Server: "			<< "[Server name]"		<< endl
		<< "Content-Length: "	<< "[Content Length]"	<< endl
		<< "Content-Type: "		<< "[Content Type]"		<< endl;
	
	if (content)
	res << endl
		<< *content;
	
	return res.str();
}
