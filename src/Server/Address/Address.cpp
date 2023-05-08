#include "Address.hpp"



/* ************************************************************************** */

void Address::parseAddress(string address, string port){
	memset(&this->data, 0, sizeof(address));
	this->data.sin_family = AF_INET;
	
	uint16_t port_tmp = 0;
	std::istringstream(port) >> port_tmp;
	this->data.sin_port = htons(port_tmp);

	int temp = 0;
	for (int i = 3; i > 0; i--){
		size_t index = address.find('.');
		if (index == string::npos){
			throw InvalidAddress();
		}
		std::istringstream(address.substr(0, index)) >> temp;
		this->data.sin_addr.s_addr += (temp << i * 8);
		address = address.substr(index + 1);
	}
	std::istringstream(address) >> temp;
	this->data.sin_addr.s_addr += temp;
}

std::ostream& operator<<(std::ostream& out, const Address& add){
	unsigned int address = add.data.sin_addr.s_addr;
	out << (address >> 24 & 0xFF) << "." << (address >> 16 & 0xFF) << "."
		<< (address >> 8 & 0xFF) << "." << (address & 0xFF)
		<< ":" << ntohs(add.data.sin_port);
	return out;
}