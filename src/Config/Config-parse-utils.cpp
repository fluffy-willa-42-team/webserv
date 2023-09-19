#include "Config.hpp"
#include "request_validation.hpp"

bool is_valid_error_code(u_int32_t code);

e_status parseline(ifstream& file, string& line, vector<string>& line_split, e_status& status){
	if (!getline(file, line)){
		status = S_END;
		return S_END;
	}

	// Remove Comments
	u_int64_t found = line.find_first_of(';');
	if (found != std::string::npos){
		line = line.substr(0, found);
	}

	if (line.size() == 0){
		status = S_PASS;
		return S_PASS;
	}

	if (line_split.size() > 0){
		line_split.clear();
	}
	
	line_split = splitStringByWhitespace(line);

	if (line_split.size() == 0){
		status = S_PASS;
		return S_PASS;
	}

	if (line_split.size() == 1 && line_split[0] == "}"){
		status = S_STOP;
		return S_STOP;
	}

	status = S_CONTINUE;
	return S_CONTINUE;
}

/******************************************************************************/

bool is_a_path(const string& input){
	return (input.size() > 0 && input[0] == '/')
		|| (input.size() > 1 && input[0] == '.' && input[1] == '/');
}

/******************************************************************************/

bool is_server_line(vector<string>& line_split){
	return line_split.size() == 2 && line_split[0] == "server" && line_split[1] == "{";
}

bool is_location_line(vector<string>& line_split){
	return line_split.size() == 3
		&& line_split[0] == string("location")
		&& line_split[1].size() > 0 && line_split[1][0] == '/'
		&& line_split[2] == string("{");
}

/******************************************************************************/

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
		&& is_a_path(line_split[2]);
}

bool is_server_option_max_client_body_size(vector<string>& line_split){
	return line_split.size() == 2
		&& line_split[0] == "max_client_body_size"
		&& stringToNumber(line_split[1]) > 0;
}

/******************************************************************************/

bool is_location_index(vector<string>& line_split){
	return line_split.size() == 2
		&& line_split[0] == "index"
		&& is_a_path(line_split[1]);
}

bool is_location_root(vector<string>& line_split){
	return line_split.size() == 2
		&& line_split[0] == "root"
		&& is_a_path(line_split[1]);
}

bool is_location_allow_methods(vector<string>& line_split){
	return line_split.size() == 2
		&& line_split[0] == "allow_methods"
		&& is_method_valid(line_split[1]) == SUCCESS;
}

bool is_location_cgi_pass(vector<string>& line_split){
	return false;
}

bool is_location_download_file(vector<string>& line_split){
	return false;
}

bool is_location_autoindex(vector<string>& line_split){
	return false;
}
