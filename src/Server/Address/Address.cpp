#include "Address.hpp"



/* ************************************************************************** */

void Address::parseAddress(string address, string port){
	memset(&this->address, 0, sizeof address);
	this->address.sin_family = AF_INET;
	
	cout << address << ":" << port << endl;
	unsigned int port_tmp = 0;
	std::istringstream(port) >> port_tmp;
	if (port_tmp > 65535)
		throw InvalidAddress();
	this->address.sin_port = port_tmp;

	int temp = 0;
	for (int i = 3; i > 0; i--){
		size_t index = address.find('.');
		if (index == string::npos){
			throw InvalidAddress();
		}
		std::istringstream(address.substr(0, index)) >> temp;
		this->address.sin_addr.s_addr += (temp << i * 8);
		address = address.substr(index + 1);
	}
	std::istringstream(address) >> temp;
	this->address.sin_addr.s_addr += temp;
}

std::ostream& operator<<(std::ostream& out, const Address& add){
	unsigned int address = add.address.sin_addr.s_addr;
	out << (address >> 24 & 0xFF) << "." << (address >> 16 & 0xFF) << "."
		<< (address >> 8 & 0xFF) << "." << (address & 0xFF)
		<< ":" << add.address.sin_port;
	return out;
}
