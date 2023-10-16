#include "request_validation.hpp"

static vector<string> default_allowed_method;
static vector<string> allowed_method;
static vector<string> not_allowed_method;

void init_allowed_method_vector(){
	default_allowed_method.push_back("GET");

	allowed_method.push_back("GET");
	allowed_method.push_back("POST");
	allowed_method.push_back("DELETE");

	not_allowed_method.push_back("HEAD");
	not_allowed_method.push_back("PUT");
	not_allowed_method.push_back("CONNECT");
	not_allowed_method.push_back("OPTIONS");
	not_allowed_method.push_back("TRACE");
	not_allowed_method.push_back("PATCH");
}

e_validation_status is_method_valid(const string& method){
	if (method.length() < 1){
		return BAD_REQUEST;
	}
	for (vector<string>::const_iterator it = allowed_method.begin(); it != allowed_method.end(); it++){
		if (method == *it){
			return SUCCESS;
		}
	}
	for (vector<string>::const_iterator it = not_allowed_method.begin(); it != not_allowed_method.end(); it++){
		if (method == *it){
			return NOT_ALLOWED;
		}
	}
	return BAD_REQUEST;
}

vector<string>& get_allowed_method(){
	return default_allowed_method;
}