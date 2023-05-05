#include "Address.hpp"

/* ************************************************************************** */

void Address::parseAddress(string address, string port){
	cout << address << ":" << port << endl;
	std::istringstream(port) >> this->port;
	if (this->port > 65535)
		throw InvalidAddress();

	int temp = 0;
	for (int i = 3; i > 0; i--){
		size_t index = address.find('.');
		if (index == string::npos){
			throw InvalidAddress();
		}
		std::istringstream(address.substr(0, index)) >> temp;
		this->address += (temp << i * 8);
		address = address.substr(index + 1);
	}
	std::istringstream(address) >> temp;
	this->address += temp;
}

std::ostream& operator<<(std::ostream& out, const Address& add){
	out << (add.address >> 24 & 0xFF) << "." << (add.address >> 16 & 0xFF) << "."
		<< (add.address >> 8 & 0xFF) << "." << (add.address & 0xFF)
		<< ":" << add.port;
	return out;
}
