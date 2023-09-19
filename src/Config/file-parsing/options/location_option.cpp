#include "file_parsing.hpp"

bool is_valid_redirect_code(u_int32_t code);

bool is_location_line(vector<string>& line_split){
	return line_split.size() == 3
		&& line_split[0] == SERVER_OPT_LOCATION
		&& line_split[1].size() > 0 && line_split[1][0] == '/'
		&& line_split[2] == PARSING_GROUP_OPENING;
}

bool is_location_index(vector<string>& line_split){
	return line_split.size() == 2
		&& line_split[0] == LOCATION_OPT_INDEX
		&& is_a_file_path(line_split[1]);
}

bool is_location_root(vector<string>& line_split){
	return line_split.size() == 2
		&& line_split[0] == LOCATION_OPT_ROOT
		&& is_a_file_path(line_split[1]);
}

bool is_location_allow_methods(vector<string>& line_split){
	if (line_split.size() <= 1 || line_split[0] != LOCATION_OPT_ALLOWED_METHODS){
		return false;
	}
	for (u_int32_t i = 1; i < line_split.size(); i++){
		if (is_method_valid(line_split[1]) != SUCCESS){
			return false;
		}
	}
	return true;
}

bool is_location_redirect(vector<string>& line_split){
	return line_split.size() == 3
		&& line_split[0] == LOCATION_OPT_REDIRECT
		&& isPositiveInteger(line_split[1])
		&& is_valid_redirect_code(stringToNumber(line_split[1]))
		&& is_a_http_path(line_split[2]);
}

bool is_location_cgi_pass(vector<string>& line_split){
	return line_split.size() == 2
		&& line_split[0] == LOCATION_OPT_CGI
		&& is_a_file_path(line_split[1]);
}

bool is_location_download_file(vector<string>& line_split){
	return line_split.size() == 2
		&& line_split[0] == LOCATION_OPT_DOWNLOAD
		&& is_bool(line_split[1]);
}

bool is_location_autoindex(vector<string>& line_split){
	return line_split.size() == 2
		&& line_split[0] == LOCATION_OPT_AUTOINDEX
		&& is_bool(line_split[1]);
}