#include "Listener.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//TODO @Matthew-Dreemurr rework for addrinfo
const string Listener::get_address(){
    stringstream ss;
	ss << inet_ntoa(address_struct.sin_addr) << ":" << port;
    return ss.str();
}
