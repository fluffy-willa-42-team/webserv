#include "Server.hpp"

const string Server::get_address(){
    stringstream ss;
	if (this->address == 0){
		ss << "localhost";
	}
	else {
		for (u_int32_t i = 0; i < 4; i++){
			ss << ((this->address >> (i * 8)) & 0xFF);
			if (i != 3){
				ss << ".";
			}
		}
	}
	ss << ":" << port;
    return ss.str();
}

bool Server::is_it_running(){
	return is_running;
}

void Server::print_waiting_msg(){
	cout << GREEN << "----- Waiting for new connection (" << get_address() << ") -----" << RESET << endl << endl;
}
