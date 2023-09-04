#include "Server.hpp"

const string Server::get_address(){
	if (this->address == 0){
		return "localhost";
	}
    stringstream ss;
	for (u_int32_t i = 0; i < 4; i++){
		ss << ((this->address >> (i * 8)) & 0xFF);
		if (i != 3){
			ss << ".";
		}
	}
	ss << ":" << port;
    return ss.str();
}
