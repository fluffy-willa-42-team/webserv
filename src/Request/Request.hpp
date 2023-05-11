#ifndef REQUEST_HPP
# define REQUEST_HPP

/* ************************************************************************** */

#include <iostream>
#include <string>

#include "webserv.hpp"
#include "Address.hpp"

/* ************************************************************************** */

class Request {
	private:
		bool valid;

		string error_message;

		class InvalidRequest : public std::exception {
			public:
				string message;
				InvalidRequest(): 						message("Invalid Request"){}
				InvalidRequest(const string& message): 	message("Invalid Request"){ this->message += ": " + message; }
				~InvalidRequest() throw() {}
				virtual const char* what() const throw() { return message.c_str(); }
		};
		
	public:
		string	method;			//	GET
		string	path;			//	/test
		string	protocol;		//	HTTP/1.1
		string	host;			//	www.example.com
		size_t	port;			//	8080

		map<string, string> headers;
		string data;

		Request(const string& input);
		Request(const Request& other);

		bool isValid(){ return valid; }

		friend std::ostream& operator<<(std::ostream& out, const Request& req);

		bool parse_line(const string& line, size_t index);
		bool parseStartLine(const string& line);
		bool parseHostHeader(const string& line);
		bool parseHeader(const string& line);
};

/* ************************************************************************** */

#endif /* REQUEST_HPP */