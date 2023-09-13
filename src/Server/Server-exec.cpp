#include "Server.hpp"

#include <unistd.h>

const string http(const string& req, Server& server);

void Server::exec(){
	string buf;

	try {
		buf = read_buff();
	}
	catch(const exception& e) {
		cerr << e.what() << '\n';
		return ;
	}
	
	cout << CYAN << buf << RESET << endl;

	// TODO Ensure the buffer has all the request

	string response = http(buf, *this);

	cout << RED << response << RESET << endl;

	write(connection_fd, response.c_str(), response.length());
	close(connection_fd);
}

string Server::read_buff(){
	memset(buffer, 0, BUFFER_SIZE);
	int32_t length_read = read(connection_fd, buffer, BUFFER_SIZE);
	if (length_read == -1){
		throw exception();
	}
	string res(buffer, length_read);
	return res;
}