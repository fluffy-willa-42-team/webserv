#include "Listener.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const string Listener::get_address(){
    stringstream ss;
	ss << inet_ntoa(address_struct.sin_addr) << ":" << port;
    return ss.str();
}

bool Listener::is_it_running(){
	return is_running;
}

void Listener::print_waiting_msg(){
	cout << GREEN << "----- Waiting for new connection (http://" << get_address() << ") -----" << RESET << endl << endl;
}
