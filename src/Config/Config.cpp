#include "Config.hpp"

vector<string>& get_allowed_method();

Location::Location()
: path(), index(), root(), cgi_pass(), allowed_methods(get_allowed_method()), download(false)
{}

Server::Server()
: host(), port(0), max_body_size(DEFAULT_MAX_BODY_SIZE), locations(), custom_error_page()
{}

e_status parseline(ifstream& file, string& line, vector<string>& line_split, e_status& status){
	if (!getline(file, line)){
		status = S_STOP;
		return S_STOP;
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
	while (parseline(config_file, line, line_split, status) != S_STOP){
		if (status == S_PASS){
			continue;
		}

		if (line_split.size() == 2 && line_split[0] == "server" && line_split[1] == "{"){
			cout << "New Server" << endl;
			while (parseline(config_file, line, line_split, status) != S_STOP){
				if (status == S_PASS){
					continue;
				}
				if (line_split.size() == 3
					&& line_split[0] == string("location")
					&& line_split[1].size() > 0 && line_split[1][0] == '/'
					&& line_split[2] == string("{")
				){
					cout << "New Location" << endl;
				}
				cout << GREEN << "\"" << line << "\"" << RESET << endl;
			}
		}
		cout << GREEN << "\"" << line << "\"" << RESET << endl;
	}

	ports.push_back(8001);
	ports.push_back(8002);
	ports.push_back(8003);


	config_file.close();
	valid = true;
}