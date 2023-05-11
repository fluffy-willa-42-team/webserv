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
		Get(Request req) : Response(req){
			cout << PURPLE << "Constructing a GET method" << RESET << endl;
		}

		string toString(){
			return "";
		}
};

/* ************************************************************************** */

#endif /* GET_HPP */