#include "Config.hpp"

map<int, string> get_status_code_map();
map<string, string> get_extension_map();

Config::Config(const string& server_name):
	name(server_name),
	version(SERVER_VERSION),
	status_codes(get_status_code_map()),
	extension_types(get_extension_map())
{}