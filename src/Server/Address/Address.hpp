#ifndef ADDRESS_HPP
# define ADDRESS_HPP

/* ************************************************************************** */

#include "using.hpp"
#include <map>
#include <iomanip>
#include <sstream>

/* ************************************************************************** */

class Address {
	public:
		unsigned int address;
		unsigned int port;

		Address(unsigned int address, unsigned int port)
			: address(address), port(port){}

		Address(string address)				: address(0), port(0) { parseAddress(address, "80"); }
		Address(string address, string port): address(0), port(0) { parseAddress(address, port); }

		void parseAddress(string address, string port);
		
		friend std::ostream& operator<<(std::ostream& out, const Address& add);

		class InvalidAddress : public std::exception { public: virtual const char* what() const throw() { return "Invalid Address"; }};
};

/* ************************************************************************** */

#endif /* ADDRESS_HPP */