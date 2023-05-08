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
		struct sockaddr_in data;

		Address(unsigned int address, unsigned int port){
			memset(&data, 0, sizeof(sockaddr_in));
			data.sin_addr.s_addr = address;
			data.sin_port = htons(port);
			data.sin_family = AF_INET;
		}
		Address(string address)				 { parseAddress(address, "80"); }
		Address(string address, string port) { parseAddress(address, port); }

		void parseAddress(string address, string port);
		
		friend std::ostream& operator<<(std::ostream& out, const Address& add);

		class InvalidAddress : public std::exception { public: virtual const char* what() const throw() { return "Invalid Address"; }};
};

/* ************************************************************************** */

#endif /* ADDRESS_HPP */