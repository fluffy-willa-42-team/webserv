#include "request_validation.hpp"

e_validation_status is_header_valid(const vector<string>& header){
	if (header.size() != 2){
		return BAD_REQUEST;
	}
	return SUCCESS;
}