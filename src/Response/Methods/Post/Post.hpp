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
		Post(Request req) : Response(req){
			cout << PURPLE << "Constructing a GET method" << RESET << endl;
		}

		string toString(){}
};

/* ************************************************************************** */

#endif /* POST_HPP */