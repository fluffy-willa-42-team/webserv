#include "file_parsing.hpp"

bool is_a_file_path(const string& input){
	return (input.size() > 0 && input[0] == '/')
		|| (input.size() > 1 && input[0] == '.' && input[1] == '/');
}

bool is_a_http_path(const string& input){
	return (input.size() > 0 && input[0] == '/');
}

bool is_bool(const string& input){
	return (input == "ON" || input == "OFF");
}
