#ifndef RESPONSE_HPP
# define RESPONSE_HPP

/* ************************************************************************** */

#include <webserv.hpp>
#include <Config.hpp>
#include <Request.hpp>
#include <Content.hpp>

/* ************************************************************************** */

class Response {
	protected:
		const Config&	config;
		const Request&	req;
		Content*		content;
		int code;

		class InvalidResponse : public std::exception {
			public:
				string message;
				InvalidResponse(): 						message("Invalid Response"){}
				InvalidResponse(const string& message):	message("Invalid Response"){ this->message += ": " + message; }
				~InvalidResponse() throw() {}
				virtual const char* what() const throw() { return message.c_str(); }
		};
	public:
		Response(const Request& req, const Config& config);
		~Response();

		virtual string toString() const = 0;

		friend Response* response_factory(const Request& req, const Config& config);

		friend std::ostream& operator<<(std::ostream& out, const Response& res);
};

Response* response_factory(const Request& req, const Config& config);

/* ************************************************************************** */

#endif /* RESPONSE_HPP */