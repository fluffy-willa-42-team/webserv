#ifndef GET_HPP
# define GET_HPP

/* ************************************************************************** */

#include <iostream>
#include <Response.hpp>

/* ************************************************************************** */

class Get : private Response {
	private:
	protected:

	public:
		Get(Request req) : Response(req){}

		std::string toString(){
			return "";
		}
};

/* ************************************************************************** */

#endif /* GET_HPP */