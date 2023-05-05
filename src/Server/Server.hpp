#ifndef SERVER_HPP
# define SERVER_HPP

/* ************************************************************************** */

#include <map>
#include <iomanip>
#include "using.hpp"
#include "Address.hpp"

/* ************************************************************************** */

class Server {
	private:
		Address address;
	public:
		Server(unsigned int address, unsigned int port): address(address, port){
			cout << "Listening on " << std::hex << std::setfill('0') << std::setw(8) << address << ":" << port << endl;
			cout << this->address << endl;
		}
};

/* ************************************************************************** */

#endif /* SERVER_HPP */