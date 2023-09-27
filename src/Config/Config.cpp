#include "Config.hpp"
#include <netdb.h>

vector<string>& get_allowed_method();

ErrorPage::ErrorPage():
code(0)
{}
ErrorPage::~ErrorPage(){}
const ErrorPage& ErrorPage::operator=(const ErrorPage& other) {
	this->code		= other.code;
	this->filepath	= other.filepath;
	this->body		= other.body;
	this->response	= other.response;
	return *this;
}

Location::Location():
path(),
index(),
root(),
cgi_pass(),
redirect_code(0),
redirect_path(),
allowed_methods(get_allowed_method()),
download(false)
{}

Location::~Location()
{}

Server::Server():
host(),
// host_data(NULL),
port(0),
max_body_size(DEFAULT_MAX_BODY_SIZE),
has_max_body_size_been_set(false),
locations(),
custom_error_page()
{}

Server::~Server()
{
}

Config::Config(const string& filename):
valid(false)
{
	ifstream config_file(filename.c_str(), std::ios_base::in);
	if (!config_file.is_open()){
		return ;
	}

	e_status status = this->parse_conf_file(config_file);
	config_file.close();
	if (status & S_ERROR){
		return ;
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