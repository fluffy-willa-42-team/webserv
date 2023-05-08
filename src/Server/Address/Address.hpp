#ifndef ADDRESS_HPP
# define ADDRESS_HPP

/* ************************************************************************** */

#include "using.hpp"
#include <map>
#include <iomanip>
#include <sstream>
#include <string.h>

#include <netinet/in.h>


/* ************************************************************************** */

class Address {
	public:
		struct sockaddr_in address;

		Address(unsigned int address, unsigned int port){
			memset(&this->address, 0, sizeof(address));
			this->address.sin_addr.s_addr = address;
			this->address.sin_port = htons(port);
			this->address.sin_family = AF_INET;
		}
		Address(string address)				 { parseAddress(address, "80"); }
		Address(string address, string port) { parseAddress(address, port); }

		void parseAddress(string address, string port);
		
		friend std::ostream& operator<<(std::ostream& out, const Address& add);

		class InvalidAddress : public std::exception { public: virtual const char* what() const throw() { return "Invalid Address"; }};
};

/* ************************************************************************** */

#endif /* ADDRESS_HPP */