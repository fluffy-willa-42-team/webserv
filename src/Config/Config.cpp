#include "Config.hpp"

vector<string>& get_allowed_method();
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
bool is_location_cgi_pass					(vector<string>& line_split);
bool is_location_download_file				(vector<string>& line_split);
bool is_location_autoindex					(vector<string>& line_split);

Location::Location()
: path(), index(), root(), cgi_pass(), allowed_methods(get_allowed_method()), download(false)
{}

Server::Server()
: host(), port(0), max_body_size(DEFAULT_MAX_BODY_SIZE), locations(), custom_error_page()
{}

Config::Config(const string& filename)
: valid(false)
{
	cout << filename << endl;

	ifstream config_file(filename.c_str(), std::ios_base::in);
	if (!config_file.is_open())
		return ;

    string line;
	vector<string> line_split;
	e_status status;
	while (!(parseline(config_file, line, line_split, status) & (S_STOP | S_END | S_ERROR))){
		if (status & S_PASS) continue;
		if (status & S_ERROR) return;
		cout << YELLOW << line << RESET << endl;

		if (!is_server_line(line_split)){
			return ;
		}

		while (!(parseline(config_file, line, line_split, status) & (S_STOP | S_END | S_ERROR))){
			if (status & S_PASS) continue;
			if (status & (S_ERROR | S_END)) return;
			cout << CYAN << line << RESET << endl;

			if (is_location_line(line_split)){
				while (!(parseline(config_file, line, line_split, status) & (S_STOP | S_END | S_ERROR))){
					if (status & S_PASS) continue;
					if (status & (S_ERROR | S_END)) return;
					if (line_split[line_split.size() - 1] == "{") return ;
					cout << GREEN << line << RESET << endl;

					if (is_location_index(line_split)){

					}
					else if (is_location_root(line_split)){

					}
					else if (is_location_allow_methods(line_split)){

					}
					else if (is_location_cgi_pass(line_split)){

					}
					else if (is_location_download_file(line_split)){

					}
					else if (is_location_autoindex(line_split)){

					}
					else {
						return ;
					}
				}
			}
			else if (is_server_option_server_name(line_split)){

			}
			else if (is_server_option_listen(line_split)){

			}
			else if (is_server_option_error_page(line_split)){

			}
			else if (is_server_option_max_client_body_size(line_split)){

			}
			else {
				return ;
			}
		}
	}

	ports.push_back(8001);
	ports.push_back(8002);
	ports.push_back(8003);


	config_file.close();
	valid = true;
}