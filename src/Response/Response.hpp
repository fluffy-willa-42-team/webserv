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
		Response(const Request& req): request(req){
			content = content_factory(req.path);
		}
		~Response(){
			delete content;
		}

		virtual string toString() = 0;
};

/* ************************************************************************** */

#endif /* RESPONSE_HPP */