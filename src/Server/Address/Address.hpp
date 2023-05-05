#ifndef ADDRESS_HPP
# define ADDRESS_HPP

/* ************************************************************************** */

#include "using.hpp"
#include <map>
#include <iomanip>

/* ************************************************************************** */

class Address {
	public:
		unsigned int address;
		unsigned int port;

		Address(unsigned int address, unsigned int port)
			: address(address), port(port){}
		
		friend std::ostream& operator<<(std::ostream& out, const Address& add){
			out << (add.address >> 24 & 0xFF) << "." << (add.address >> 16 & 0xFF) << "."
				<< (add.address >> 8 & 0xFF) << "." << (add.address & 0xFF)
				<< ":" << add.port;
			return out;
		}
};

/* ************************************************************************** */

#endif /* ADDRESS_HPP */