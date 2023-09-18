#ifndef CONFIG_HPP
# define CONFIG_HPP

/******************************************************************************/

#include "webserv.hpp"
#include "utils.hpp"

/******************************************************************************/

# define DEFAULT_MAX_BODY_SIZE 64

/******************************************************************************/

class Location {
	public:
		Location();

		string			path;
		string			index;
		string			root;
		string			cgi_pass;
		vector<string>	allowed_methods;
		bool			download;
};

/******************************************************************************/

class Server {
	public:
		Server();

		string					host;
		u_int32_t				port;
		int32_t					max_body_size;
		vector<Location>		locations;
		map<u_int32_t, string>	custom_error_page;
};

/******************************************************************************/

class Config {
	public:
		bool				valid;
		vector<u_int32_t>	ports;
		vector<Server>		servers;

		Config(const string& filename);
};

/******************************************************************************/

#endif /* CONFIG_HPP */