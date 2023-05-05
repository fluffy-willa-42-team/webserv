#ifndef REQUEST_HPP
# define REQUEST_HPP

/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <string>

#include "using.hpp"

/* ************************************************************************** */

class Request {
	private:
		bool valid;

		string method;			//	GET
		string path;			//	/test
		string protocol;		//	HTTP/1.1
		string host;			//	www.example.com
		size_t port;			//	8080

		map<string, string> headers;
		string data;

		class InvalidRequest : public std::exception {
			public:
				string message;
				InvalidRequest(): 						message("Invalid Request"){}
				InvalidRequest(const string& message): 	message("Invalid Request"){ this->message += ": " + message; }
				~InvalidRequest() throw() {}
				virtual const char* what() const throw() { return this->message.c_str(); }
		};
		
	public:
		Request(const std::string& input);

		bool isValid(){ return this->valid; }

		friend std::ostream& operator<<(std::ostream& out, const Request& req);

		bool parse_line(const string& line, size_t index);
		bool parseStartLine(const string& line);
		bool parseHostHeader(const string& line);
		bool parseHeader(const string& line);
};

/* ************************************************************************** */

#endif /* REQUEST_HPP */