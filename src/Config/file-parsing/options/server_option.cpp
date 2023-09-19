#include "file_parsing.hpp"

bool is_valid_error_code(u_int32_t code);

bool is_server_line(vector<string>& line_split){
	return line_split.size() == 2 && line_split[0] == "server" && line_split[1] == "{";
}

bool is_server_option_server_name(vector<string>& line_split){
	return line_split.size() > 1
		&& line_split[0] == "server_name";
}

bool is_server_option_listen(vector<string>& line_split){
	if (!(line_split.size() == 2 && line_split[0] == "listen")){
		return false;
	}
	if (stringToNumber(line_split[1]) == 0){
		vector<string> splited = split(line_split[1], ":");
		if (splited.size() != 2
			// TODO ? verify if host is valid
			|| stringToNumber(splited[1]) == 0
		){
			return false;
		}
	}
	return true;
}

bool is_server_option_error_page(vector<string>& line_split){
	return line_split.size() == 3
		&& line_split[0] == "error_page"
		&& is_valid_error_code(stringToNumber(line_split[1]))
		&& is_a_file_path(line_split[2]);
}

bool is_server_option_max_client_body_size(vector<string>& line_split){
	return line_split.size() == 2
		&& line_split[0] == "max_client_body_size"
		&& stringToNumber(line_split[1]) > 0;
}
