#ifndef RESPONSE_HPP
# define RESPONSE_HPP

/* ************************************************************************** */

#include <Request.hpp>
#include <Content.hpp>
#include <webserv.hpp>

/* ************************************************************************** */

class Response {
	protected:
		const Request&	req;
		Content*		content;

		class InvalidResponse : public std::exception {
			public:
				string message;
				InvalidResponse(): 						message("Invalid Response"){}
				InvalidResponse(const string& message):	message("Invalid Response"){ this->message += ": " + message; }
				~InvalidResponse() throw() {}
				virtual const char* what() const throw() { return message.c_str(); }
		};
	public:
		Response(const Request& req);
		~Response();

		virtual string toString() const = 0;

		friend Response* response_factory(const Request& req);

		friend std::ostream& operator<<(std::ostream& out, const Response& res);
};

Response* response_factory(const Request& req);

/* ************************************************************************** */

#endif /* RESPONSE_HPP */