#include "Server.hpp"

static const string print_address(u_int32_t address){
	if (address == 0){
		return "localhost";
	}
    stringstream ss;
	for (u_int32_t i = 0; i < 4; i++){
		ss << ((address >> (i * 8)) & 0xFF);
		if (i != 3){
			ss << ".";
		}
	}
    return ss.str();
}

Server::Server(u_int32_t address, u_int16_t port)
: address(address), port(port)
{
	cout << "Starting Server      : " << print_address(address) << ":" << port << endl;
}

Server::~Server(){
	cout << "Shutting down Server : " << print_address(address) << ":" << port << endl;
}