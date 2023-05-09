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
		Get();
		~Get();
		Get(const Get& other);
		const Get& operator=(const Get& other);

		std::string toString(){}
};

/* ************************************************************************** */

#endif /* GET_HPP */