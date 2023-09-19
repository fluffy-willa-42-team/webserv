#include "Config.hpp"

e_status parseline(ifstream& file, string& line, vector<string>& line_split, e_status& status);
bool is_server_line							(vector<string>& line_split);
bool is_location_line						(vector<string>& line_split);
bool is_server_option_server_name			(vector<string>& line_split);
bool is_server_option_listen				(vector<string>& line_split);
bool is_server_option_error_page			(vector<string>& line_split);
bool is_server_option_max_client_body_size	(vector<string>& line_split);
bool is_location_index						(vector<string>& line_split);
bool is_location_root						(vector<string>& line_split);
bool is_location_allow_methods				(vector<string>& line_split);
bool is_location_return						(vector<string>& line_split);
bool is_location_cgi_pass					(vector<string>& line_split);
bool is_location_download_file				(vector<string>& line_split);
bool is_location_autoindex					(vector<string>& line_split);

static e_status err(const string& line){
	cerr << "-> \"" << RED << line << RESET << "\"" << endl;
	return S_ERROR;
}

e_status Config::parse_conf_file(ifstream& config_file){
	string line;
	vector<string> line_split;
	e_status status;
	while (!(parseline(config_file, line, line_split, status) & S_END)){
		if (status & S_PASS) continue;
		if (status & (S_ERROR | S_STOP) || !is_server_line(line_split)){
			return err(line);
		}

		while (!(parseline(config_file, line, line_split, status) & S_STOP)){
			if (status & S_PASS) continue;
			if (status & (S_ERROR | S_END)){
				return err(line);
			}

			if (is_location_line(line_split)){
				while (!(parseline(config_file, line, line_split, status) & S_STOP)){
					if (status & S_PASS) continue;
					if ((status & (S_ERROR | S_END)) || line_split[line_split.size() - 1] == "{"){
						return err(line);
					}

					if (is_location_index(line_split)){}
					else if (is_location_root(line_split)){}
					else if (is_location_allow_methods(line_split)){}
					else if (is_location_return(line_split)){}
					else if (is_location_cgi_pass(line_split)){}
					else if (is_location_download_file(line_split)){}
					else if (is_location_autoindex(line_split)){}
					else {
						return err(line);
					}
				}
			}
			else if (is_server_option_server_name(line_split)){}
			else if (is_server_option_listen(line_split)){}
			else if (is_server_option_error_page(line_split)){}
			else if (is_server_option_max_client_body_size(line_split)){}
			else {
				return err(line);
			}
		}
	}
	return S_CONTINUE;
}
