#include "Config.hpp"

vector<string>& get_allowed_method();


Location::Location():
path(),
index(),
root(),
cgi_pass(),
allowed_methods(get_allowed_method()),
download(false),
type(E_NOT_SET)
{}

Location::~Location()
{}

Server::Server():
host(),
port(0),
max_body_size(DEFAULT_MAX_BODY_SIZE),
has_max_body_size_been_set(false),
locations(),
custom_error_page()
{}

Server::~Server()
{}

Config::Config(const string& filename):
valid(false)
{
	ifstream config_file(filename.c_str(), std::ios_base::in);
	if (!config_file.is_open()){
		return ;
	}

	{
		e_status status = this->parse_conf_file(config_file);
		config_file.close();
		if (status & S_ERROR){
			return ;
		}
	}

	{
		e_status status = this->test_if_file_or_folder_exist();
		if (status & S_ERROR){
			return ;
		}
	}

	if (servers.size() < 1){
		cerr << RED << "No Server found" << RESET << endl;
		return ;
	}

	valid = true;
}

Config::~Config()
{}

bool Location::operator<(const Location& other) const{
	return this->path.size() > other.path.size();
}