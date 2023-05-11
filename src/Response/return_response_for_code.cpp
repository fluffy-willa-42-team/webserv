#include "webserv.hpp"
#include "Config.hpp"

string response_for_code(int code, const Config& config){
	stringstream ss1;
	ss1	<< "<html>"
		<< "    <h1>"
		<<          code << ": " << config.status_codes.at(code)
		<< "    </h1>"
		<< "</html>";

	string message = ss1.str();

	stringstream ss2;
	ss2	<< PROTOCOL << " " << code << " " << config.status_codes.at(code) << endl
		<< "Date: " << get_now() << endl
		<< "Server: " << config.name << endl
		<< "Content-Type: " << "text/html" << endl
		<< "Content-Length: " << message.length() << endl
		<< endl
		<< message;

	return ss2.str();
}