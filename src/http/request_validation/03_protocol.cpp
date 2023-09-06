#include "request_validation.hpp"

e_validation_status is_protocol_valid(const string& protocol){
	if (protocol == PROTOCOL){
		return SUCCESS;
	}
	if (protocol.find("HTTP/") != string::npos){
		return NOT_ALLOWED;
	}
	return BAD_REQUEST;
}