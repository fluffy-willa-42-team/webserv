#include "Listener.hpp"
#include "http.hpp"
#include <unistd.h>

#include "debug.hpp"

void Listener::exec(const Config& config){
	string buf;

	try {
		buf = read_buff();
	}
	catch(const exception& e) {
		cerr << e.what() << '\n';
		return ;
	}
	
	DEBUG_INFO_ << "Request: " << buf;

	string response = http(buf, *this, config);

	// DEBUG_INFO_ << RED << "Response: " << endl << response << endl << RESET;

	write(connection_fd, response.c_str(), response.length());
	close(connection_fd);
}

string Listener::read_buff(){
	memset(buffer, 0, BUFFER_SIZE);
	int32_t length_read = read(connection_fd, buffer, BUFFER_SIZE);
	if (length_read == -1){
		DEBUG_WARN_ << "Failed to read from socket";
		throw exception();
	}
	return string(buffer, length_read);
}