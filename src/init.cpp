#include "webserv.hpp"

void init_error_map();
void init_redirect_map();
void init_allowed_method_vector();
void init_content_type();
bool init_static_file();
void init_codes_map();

bool init(){
	init_codes_map();
	init_allowed_method_vector();
	init_content_type();
	if (!init_static_file()){
		return false;
	}
	return true;
}