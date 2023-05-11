#include "webserv.hpp"

#include <ctime>
#include <cstring>

string get_now(){
	std::time_t now = std::time(NULL);
	std::tm* tm = std::localtime(&now);

	char buffer[80];
	memset(buffer, 0, 80);
    std::strftime(buffer, 80, "%a, %d %b %Y %H:%M:%S GMT", tm);

	return string(buffer);
}