#ifndef GET_HPP
# define GET_HPP

/* ************************************************************************** */

#include <Response.hpp>

/* ************************************************************************** */

class Get : public Response {
	private:
		// uint32_t 
	public:
		Get(const Request& req, const Config& config);

		string toString() const;
};

/* ************************************************************************** */

#endif /* GET_HPP */