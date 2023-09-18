#include "Server.hpp"

const string Server::get_address(){
    stringstream ss;
	ss << "localhost" << ":" << port;
    return ss.str();
}

bool Server::is_it_running(){
	return is_running;
}

void Server::print_waiting_msg(){
	cout << GREEN << "----- Waiting for new connection (http://" << get_address() << ") -----" << RESET << endl << endl;
}
