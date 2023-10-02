#include "webserv.hpp"

void init_allowed_method_vector();
void init_content_type();
bool init_static_file();
void init_codes_map();
void init_default_codes();

bool init(Env& env, char* envp[]){
	init_codes_map();
	init_allowed_method_vector();
	init_content_type();
	init_default_codes();
	if (!init_static_file()){
		return false;
	}
    for (int i = 0; envp[i] != NULL; ++i) {
        env.push_back(envp[i]);
    }
	return true;
}