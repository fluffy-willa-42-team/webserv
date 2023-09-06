#include "webserv.hpp"

void init_error_map();
void init_allowed_method_vector();

void init(){
	init_error_map();
	init_allowed_method_vector();
}