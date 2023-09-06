#include "webserv.hpp"

bool is_path_valid(const string& path){
	if (path.length() < 1
		|| path[0] != '/'
	){
		return false;
	}
	return true;
}
