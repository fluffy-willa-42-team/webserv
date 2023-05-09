#ifndef RESPONSE_HPP
# define RESPONSE_HPP

/* ************************************************************************** */

#include <Request.hpp>
#include <Content.hpp>
#include <using.hpp>

/* ************************************************************************** */

class Response {
	protected:
		const Request&	request;
		Content*		content;

	public:
		Response(Request req): request(req){}
		~Response(){
			delete content;
		}

		virtual std::string toString() = 0;
};

/* ************************************************************************** */

#endif /* RESPONSE_HPP */