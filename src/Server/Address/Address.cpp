#include "Address.hpp"

/* ************************************************************************** */

void Address::parseAddress(string address, string port){
	cout << address << ":" << port << endl;
	std::istringstream(port) >> this->port;
	if (this->port > 65535)
		throw InvalidAddress();
	for (int i = 0; i < 3; i++){
		size_t index = address.find('.');
		if (index == string::npos){
			throw InvalidAddress();
		}
		cout << ">" << address.substr(0, index) << endl;
		address = address.substr(index + 1);
	}
	cout << ">" << address << endl;
}

std::ostream& operator<<(std::ostream& out, const Address& add){
	out << (add.address >> 24 & 0xFF) << "." << (add.address >> 16 & 0xFF) << "."
		<< (add.address >> 8 & 0xFF) << "." << (add.address & 0xFF)
		<< ":" << add.port;
	return out;
}
