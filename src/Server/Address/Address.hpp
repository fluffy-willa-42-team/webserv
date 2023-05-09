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
		sockaddr_in data;
		uint32_t len;

		Address(unsigned int address, unsigned int port) : len(sizeof(sockaddr_in)) {
			data.sin_addr.s_addr = address;
			data.sin_port = htons(port);
			data.sin_family = AF_INET;
		}
		Address(string address)				 : len(sizeof(sockaddr_in)) { parseAddress(address, "80"); }
		Address(string address, string port) : len(sizeof(sockaddr_in)) { parseAddress(address, port); }

		sockaddr* get_sockaddr(){ return ((sockaddr *)&data); }
		void parseAddress(string address, string port);
		
		friend std::ostream& operator<<(std::ostream& out, const Address& add);

		class InvalidAddress : public std::exception { public: virtual const char* what() const throw() { return "Invalid Address"; }};
};

/* ************************************************************************** */

#endif /* ADDRESS_HPP */