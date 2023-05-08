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
		Server(unsigned int address, unsigned int port) : address(address, port){
			cout << "Listening on " << this->address << endl;
		}

		Server(Address add) : address(add.address.sin_addr.s_addr, add.address.sin_port){
			cout << "Listening on " << this->address << endl;
		}
};

/* ************************************************************************** */

#endif /* SERVER_HPP */