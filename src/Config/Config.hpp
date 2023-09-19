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
		string			path;
		string			index;
		string			root;
		string			cgi_pass;
		vector<string>	allowed_methods;
		bool			download;
		bool			autoindex;

		Location();
		~Location();
};

/******************************************************************************/

class Server {
	public:
		string					host;
		u_int32_t				port;
		int32_t					max_body_size;
		bool					has_max_body_size_been_set;
		vector<Location>		locations;
		map<u_int32_t, string>	custom_error_page;

		Server();
		~Server();
};

/******************************************************************************/

class Config {
	public:
		bool				valid;
		vector<u_int32_t>	ports;
		vector<Server>		servers;

		Config(const string& filename);

	private:
		e_status parse_conf_file(ifstream& config_file);
};

/******************************************************************************/

#endif /* CONFIG_HPP */