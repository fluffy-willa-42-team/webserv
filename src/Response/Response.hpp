#ifndef RESPONSE_HPP
# define RESPONSE_HPP

/* ************************************************************************** */

#include <iostream>
#include <ResponseHeader.hpp>

/* ************************************************************************** */

class Response {
	private:
		ResponseHeader header;
	protected:

	public:
		Response();
		~Response();
		Response(const Response& other);
		const Response& operator=(const Response& other);

		virtual std::string toString() = 0;
		
};

/* ************************************************************************** */

#endif /* RESPONSE_HPP */