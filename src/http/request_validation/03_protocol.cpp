#include "request_validation.hpp"

bool is_protocol_valid(const string& path){
	return path == PROTOCOL;
}