#include "Config.hpp"

vector<string>& get_allowed_method();

Location::Location()
: path(), index(), root(), cgi_pass(), allowed_methods(get_allowed_method()), download(false)
{}

Server::Server()
: host(), port(0), max_body_size(DEFAULT_MAX_BODY_SIZE), locations(), custom_error_page()
{}
