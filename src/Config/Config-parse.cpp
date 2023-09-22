#include "Config.hpp"
#include "file_parsing.hpp"
#include <algorithm>

static e_status err(const string& line, const u_int32_t& index, const string& message = ""){
	cerr << RED << "[" << index << "] \"" << line << "\"" << RESET << endl;
	if (!message.empty()){
		cerr << RED << "=> " << message << RESET << endl;
	}
	return S_ERROR;
}

static bool is_type_valid(e_location_type& type, e_location_type newType){
	if (type == E_NOT_SET){
		type = newType;
	}
	else if (type != newType){
		return false;
	}
	return true;
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

		Server newServer;
		while (!(parseline(config_file, line, line_split, status, index) & S_STOP)){
			if (status & S_PASS) continue;
			if (status & (S_ERROR | S_END)){
				return err(line, index);
			}

			if (is_server_option_server_name(line_split)){
				if (newServer.host.size() > 0){
					return err(line, index, "Duplicate Parameter");
				}
				newServer.host = line_split[1];
			}
			else if (is_server_option_listen(line_split)){
				if (newServer.port != 0){
					return err(line, index, "Duplicate Parameter");
				}
				if (isPositiveInteger(line_split[1])){
					newServer.port = stringToNumber(line_split[1]);
				}
				else {
					vector<string> splited = split(line_split[1], ":");
					if (!isPositiveInteger(splited[1])){
						return err(line, index);
					}
					newServer.port = stringToNumber(splited[1]);
					if (!(newServer.port == 80 || newServer.port == 443
						|| (1024 <= newServer.port && newServer.port <= 65535))){
						return err(line, index);
					}
				}
			}
			else if (is_server_option_error_page(line_split)){
				// if (!isFileReadable(line_split[2])){
				// 	return err(line, index, "Can't open error file");
				// }
				newServer.custom_error_page[stringToNumber(line_split[1])] = line_split[2];
			}
			else if (is_server_option_max_client_body_size(line_split)){
				if (newServer.has_max_body_size_been_set){
					return err(line, index, "Duplicate Parameter");
				}
				if (!isPositiveInteger(line_split[1])){
					return err(line, index);
				}
				newServer.max_body_size = stringToNumber(line_split[1]);
				newServer.has_max_body_size_been_set = true;
			}
			else if (is_location_line(line_split)){
				Location newLocation;
				newLocation.path = line_split[1];
				while (!(parseline(config_file, line, line_split, status, index) & S_STOP)){
					if (status & S_PASS) continue;
					if ((status & (S_ERROR | S_END)) || line_split[line_split.size() - 1] == PARSING_GROUP_OPENING){
						return err(line, index);
					}

					if (is_location_index(line_split)){
						if (!is_type_valid(newLocation.type, E_NORMAL)){
							return err(line, index, "Incompatible location arguments");
						}
						newLocation.index = line_split[1];
					}
					else if (is_location_root(line_split)){
						if (!is_type_valid(newLocation.type, E_NORMAL)){
							return err(line, index, "Incompatible location arguments");
						}
						newLocation.root = line_split[1];
					}
					else if (is_location_allow_methods(line_split)){
						if (!is_type_valid(newLocation.type, E_NORMAL)){
							return err(line, index, "Incompatible location arguments");
						}
						for (u_int32_t i = 1; i < line_split.size(); i++){
							newLocation.allowed_methods.push_back(line_split[i]);
						}
					}
					else if (is_location_redirect(line_split)){
						if (!is_type_valid(newLocation.type, E_REDIRECT)){
							return err(line, index, "Incompatible location arguments");
						}
						if (!newLocation.redirect_path.empty() || newLocation.redirect_code != 0){
							return (err(line, index, "Duplicate Parameter"));
						}
						newLocation.redirect_path = line_split[2];
					}
					else if (is_location_cgi_pass(line_split)){
						if (!is_type_valid(newLocation.type, E_NORMAL)){
							return err(line, index, "Incompatible location arguments");
						}
						newLocation.cgi_pass = line_split[1];
					}
					else if (is_location_download_file(line_split)){
						if (!is_type_valid(newLocation.type, E_NORMAL)){
							return err(line, index, "Incompatible location arguments");
						}
						if (line_split[1] == "ON"){
							newLocation.download = true;
						}
						else if (line_split[1] == "OFF"){
							newLocation.download = false;
						}
					}
					else if (is_location_autoindex(line_split)){
						if (!is_type_valid(newLocation.type, E_NORMAL)){
							return err(line, index, "Incompatible location arguments");
						}
						if (line_split[1] == "ON"){
							newLocation.autoindex = true;
						}
						else if (line_split[1] == "OFF"){
							newLocation.autoindex = false;
						}
					}
					else {
						return err(line, index);
					}
				}
				newServer.locations.push_back(newLocation);
			}
			else {
				return err(line, index);
			}
		}
		std::sort(newServer.locations.begin(), newServer.locations.end());
		servers.push_back(newServer);
		ports.push_back(newServer.port);
	}
	return S_CONTINUE;
}
