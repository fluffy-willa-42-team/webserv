#include "webserv.hpp"

static vector<string> allowed_method;

void init_allowed_method_vector(){
	allowed_method.push_back("GET");
	allowed_method.push_back("POST");
	// allowed_method.push_back("PUT");
	allowed_method.push_back("DELETE");
}

bool is_method_valid(const string& method){
	if (method.length() < 1){
		return false;
	}
	for (vector<string>::iterator it = allowed_method.begin(); it != allowed_method.end(); it++){
		if (method == *it){
			return true;
		}
	}
	return false;
}