#include "Config.hpp"

vector<string>& get_allowed_method();

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


	ports.push_back(8001);
	ports.push_back(8002);
	ports.push_back(8003);


	config_file.close();
	valid = true;
}