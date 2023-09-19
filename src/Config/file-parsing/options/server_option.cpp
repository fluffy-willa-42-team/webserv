#include "file_parsing.hpp"

bool is_valid_error_code(u_int32_t code);

bool is_server_line(vector<string>& line_split){
	return line_split.size() == 2
		&& line_split[0] == SERVER_OPT
		&& line_split[1] == PARSING_GROUP_OPENING;
}

bool is_server_option_server_name(vector<string>& line_split){
	return line_split.size() == 2
		&& line_split[0] == SERVER_OPT_SERVER_NAME;
}

bool is_server_option_listen(vector<string>& line_split){
	if (!(line_split.size() == 2 && line_split[0] == SERVER_OPT_LISTEN)){
		return false;
	}
	if (!isPositiveInteger(line_split[1])){
		vector<string> splited = split(line_split[1], ":");
		// TODO ? verify if host is valid
		if (!(splited.size() == 2 && isPositiveInteger(splited[1]))
		){
			return false;
		}
	}
	return true;
}

bool is_server_option_error_page(vector<string>& line_split){
	return line_split.size() == 3
		&& line_split[0] == SERVER_OPT_ERROR_PAGE
		&& isPositiveInteger(line_split[1])
		&& is_valid_error_code(stringToNumber(line_split[1]))
		&& is_a_file_path(line_split[2]);
}

bool is_server_option_max_client_body_size(vector<string>& line_split){
	return line_split.size() == 2
		&& line_split[0] == SERVER_OPT_MAX_BOBY_SIZE
		&& isPositiveInteger(line_split[1])
		&& stringToNumber(line_split[1]) > 0;
}
