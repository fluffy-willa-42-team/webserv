#ifndef DELETE_HPP
# define DELETE_HPP

/* ************************************************************************** */

#include <iostream>
#include <Response.hpp>

/* ************************************************************************** */

class Delete : public Response {
	private:
		// uint32_t 
	public:
		Delete(const Request& req, const Config& config);

		string toString() const;
};

/* ************************************************************************** */

#endif /* DELETE_HPP */