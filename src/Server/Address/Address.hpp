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
		sockaddr_in input;
		sockaddr data;
		uint32_t len;

		Address(unsigned int address, unsigned int port) : len(sizeof(sockaddr_in)) {
			memset(&input, 0, len);
			input.sin_addr.s_addr = address;
			input.sin_port = htons(port);
			input.sin_family = AF_INET;
		}
		Address(string address)				 : len(sizeof(sockaddr_in)) { parseAddress(address, "80"); }
		Address(string address, string port) : len(sizeof(sockaddr_in)) { parseAddress(address, port); }

		void parseAddress(string address, string port);

		socklen_t* get_socklen() { return ((socklen_t *)&len); }
		
		friend std::ostream& operator<<(std::ostream& out, const Address& add);

		class InvalidAddress : public std::exception { public: virtual const char* what() const throw() { return "Invalid Address"; }};
};

/* ************************************************************************** */

#endif /* ADDRESS_HPP */