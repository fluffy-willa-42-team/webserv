#ifndef GET_HPP
# define GET_HPP

/* ************************************************************************** */

#include <iostream>
#include <Response.hpp>

/* ************************************************************************** */

class Get : public Response {
	private:
	protected:

	public:
		Get(const Request& req);

		string toString() const;
};

/* ************************************************************************** */

#endif /* GET_HPP */