#include "Listener.hpp"

const string Listener::get_address(){
    stringstream ss;
	ss << "localhost" << ":" << port;
    return ss.str();
}

bool Listener::is_it_running(){
	return is_running;
}

void Listener::print_waiting_msg(){
	cout << GREEN << "----- Waiting for new connection (http://" << get_address() << ") -----" << RESET << endl << endl;
}

const Config* Listener::get_config(){
	return this->config;
}