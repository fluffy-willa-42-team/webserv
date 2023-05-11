#include "Server.hpp"
#include "Request.hpp"
#include "Response.hpp"

#define TEST_MESSAGE "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: "

string get_message_test(const Request &req){
	stringstream ss1;
	ss1 << req;

	stringstream ss;
    ss << TEST_MESSAGE << ss1.str().length() << "\n\n" << ss1.str();
    string message = ss.str();
	return message;
}

void Server::exec(){
	read(connection_fd, buffer, BUFFER_SIZE);
	cout << buffer << endl;

	Request req(buffer);

	Response* res = response_factory(req, config);
	if (!res)
		cout << "EREREROOOR" << endl;

	string message = res->toString();
	write(connection_fd , message.c_str(), message.length());
	
	reset_buffer();

	close(connection_fd);
}