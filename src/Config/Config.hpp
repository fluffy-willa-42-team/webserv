#ifndef CONFIG_HPP
# define CONFIG_HPP

/******************************************************************************/

#include "webserv.hpp"
#include "utils.hpp"

/******************************************************************************/

# define DEFAULT_MAX_BODY_SIZE 64

#define SERVER_OPT						"server"
#define SERVER_OPT_SERVER_NAME			"server_name"
#define SERVER_OPT_LISTEN				"listen"
#define SERVER_OPT_ERROR_PAGE			"error_page"
#define SERVER_OPT_MAX_BOBY_SIZE		"max_client_body_size"
#define SERVER_OPT_LOCATION				"location"
#define LOCATION_OPT_INDEX				"index"
#define LOCATION_OPT_ROOT				"root"
#define LOCATION_OPT_ALLOWED_METHODS	"allow_methods"
#define LOCATION_OPT_REDIRECT			"redirect"
#define LOCATION_OPT_CGI				"cgi_pass"
#define LOCATION_OPT_DOWNLOAD			"download"
#define LOCATION_OPT_AUTOINDEX			"autoindex"
#define PARSING_GROUP_OPENING			"{"
#define PARSING_GROUP_CLOSING			"}"

/******************************************************************************/

class Location {
	public:
		string			path;
		string			index;
		string			root;
		string			cgi_pass;
		u_int32_t		redirect_code;
		string			redirect_path;
		vector<string>	allowed_methods;
		bool			download;
		bool			autoindex;
		bool 			has_redirect;
		bool 			has_index;
		bool 			has_root;
		bool 			has_root_param;

		Location();
		~Location();

		bool operator<(const Location& other) const;
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
		~Config();

	private:
		e_status parse_conf_file(ifstream& config_file);
		e_status test_if_file_or_folder_exist();
};

/******************************************************************************/

#endif /* CONFIG_HPP */