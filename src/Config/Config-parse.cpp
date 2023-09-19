#include "Config.hpp"
#include "file_parsing.hpp"

static e_status err(const string& line, const u_int32_t& index){
	cerr << RED << "[" << index << "] \"" << line << "\"" << RESET << endl;
	return S_ERROR;
}

e_status Config::parse_conf_file(ifstream& config_file){
	string line;
	vector<string> line_split;
	e_status status;
	u_int32_t index = 0;
	while (!(parseline(config_file, line, line_split, status, index) & S_END)){
		if (status & S_PASS) continue;
		if (status & (S_ERROR | S_STOP) || !is_server_line(line_split)){
			return err(line, index);
		}

		while (!(parseline(config_file, line, line_split, status, index) & S_STOP)){
			if (status & S_PASS) continue;
			if (status & (S_ERROR | S_END)){
				return err(line, index);
			}

			if (is_location_line(line_split)){
				while (!(parseline(config_file, line, line_split, status, index) & S_STOP)){
					if (status & S_PASS) continue;
					if ((status & (S_ERROR | S_END)) || line_split[line_split.size() - 1] == "{"){
						return err(line, index);
					}

					if (is_location_index(line_split)){}
					else if (is_location_root(line_split)){}
					else if (is_location_allow_methods(line_split)){}
					else if (is_location_return(line_split)){}
					else if (is_location_cgi_pass(line_split)){}
					else if (is_location_download_file(line_split)){}
					else if (is_location_autoindex(line_split)){}
					else {
						return err(line, index);
					}
				}
			}
			else if (is_server_option_server_name(line_split)){}
			else if (is_server_option_listen(line_split)){}
			else if (is_server_option_error_page(line_split)){}
			else if (is_server_option_max_client_body_size(line_split)){}
			else {
				return err(line, index);
			}
		}
	}
	return S_CONTINUE;
}
