#include "Server.hpp"

#include <unistd.h>

#define response_example "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 112\n\n<html>\n<head>\n   <title>200 OK</title>\n</head>\n<body>\n   <h1>OK</h1>\n   <p>The request was successful.</p>\n</body>\n</html>"

void Server::exec(){
	read(connection_fd, buffer, BUFFER_SIZE);
	cout << CYAN << buffer << RESET << endl;

	string message(response_example);

	cout << message << endl;

	write(connection_fd , message.c_str(), message.length());
	
	memset(buffer, 0, BUFFER_SIZE);

	close(connection_fd);
}