#include "Server.hpp"
#include "Request.hpp"
#include "Get.hpp"

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

	Request test(buffer);

	cout << BLUE << "----- Test Request -----" << RESET << endl << endl;

	Get get(test, config);

	cout << test << endl;

	string message = get_message_test(test);
	write(connection_fd , message.c_str(), message.length());
	
	reset_buffer();

	close(connection_fd);
}