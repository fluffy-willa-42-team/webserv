#include "response.hpp"

map<string, u_int32_t> default_codes;

void init_default_codes(){
	default_codes["GET"]	= 200;
	default_codes["POST"]	= 201;
	default_codes["PATCH"]	= 200;
	default_codes["PUT"]	= 200;
	default_codes["DELETE"]	= 204;
}