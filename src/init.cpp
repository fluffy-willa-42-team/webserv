#include "webserv.hpp"

void init_error_map();
void init_redirect_map();
void init_allowed_method_vector();
void init_content_type();

void init(){
	init_error_map();
	init_redirect_map();
	init_allowed_method_vector();
	init_content_type();
}