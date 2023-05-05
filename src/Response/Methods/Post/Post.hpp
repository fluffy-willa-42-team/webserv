#ifndef POST_HPP
# define POST_HPP

/* ************************************************************************** */

#include <iostream>
#include <Response.hpp>

/* ************************************************************************** */

class Post : private Response {
	private:
	protected:

	public:
		Post();
		~Post();
		Post(const Post& other);
		const Post& operator=(const Post& other);

		std::string toString(){}
};

/* ************************************************************************** */

#endif /* POST_HPP */