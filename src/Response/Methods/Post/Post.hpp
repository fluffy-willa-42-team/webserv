#ifndef POST_HPP
# define POST_HPP

/* ************************************************************************** */

#include <iostream>
#include <Response.hpp>

/* ************************************************************************** */

class Post : public Response {
	private:
	protected:

	public:
		Post(Request req) : Response(req){
			cout << PURPLE << "Constructing a GET method" << RESET << endl;
		}

		string toString() const {
			return "";
		}
};

/* ************************************************************************** */

#endif /* POST_HPP */