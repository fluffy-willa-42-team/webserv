#include "Address.hpp"



/* ************************************************************************** */

void Address::parseAddress(string address, string port){
	memset(&data, 0, sizeof(sockaddr_in));
	data.sin_family = AF_INET;
	
	uint16_t port_tmp = 0;
	stringstream(port) >> port_tmp;
	data.sin_port = htons(port_tmp);

	int temp = 0;
	for (int i = 3; i > 0; i--){
		size_t index = address.find('.');
		if (index == string::npos){
			throw InvalidAddress();
		}
		stringstream(address.substr(0, index)) >> temp;
		data.sin_addr.s_addr += (temp << i * 8);
		address = address.substr(index + 1);
	}
	stringstream(address) >> temp;
	data.sin_addr.s_addr += temp;
}

std::ostream& operator<<(std::ostream& out, const Address& add){
	unsigned int address = add.data.sin_addr.s_addr;
	out << (address >> 24 & 0xFF) << "." << (address >> 16 & 0xFF) << "."
		<< (address >> 8 & 0xFF) << "." << (address & 0xFF)
		<< ":" << ntohs(add.data.sin_port);
	return out;
}
