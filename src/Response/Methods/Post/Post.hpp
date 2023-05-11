#ifndef POST_HPP
# define POST_HPP

/* ************************************************************************** */

#include <iostream>
#include <Response.hpp>

/* ************************************************************************** */

class Post : public Response {
	private:
		// uint32_t 
	public:
		Post(const Request& req, const Config& config);

		string toString() const;
};

/* ************************************************************************** */

#endif /* POST_HPP */