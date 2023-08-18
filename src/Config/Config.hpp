#ifndef CONFIG_HPP
# define CONFIG_HPP

/* ************************************************************************** */

#include "webserv.hpp"

/* ************************************************************************** */

class Config {
	public:
		string name;
		string version;
		map<int, string> status_codes;
		map<string, string> extension_types;

		// map<string, string> paths;

		Config(const string& server_name);

		friend std::ostream& operator<<(std::ostream& out, const Config& req);

		class InvalidConfig : public std::exception {
			public:
				string message;
				InvalidConfig(): 						message("Invalid Config"){}
				InvalidConfig(const string& message): 	message("Invalid Config"){ this->message += ": " + message; }
				~InvalidConfig() throw() {}
				virtual const char* what() const throw() { return message.c_str(); }
		};
};

string get_now();

/* ************************************************************************** */

#endif /* CONFIG_HPP */