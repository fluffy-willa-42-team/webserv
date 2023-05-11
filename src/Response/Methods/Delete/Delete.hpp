#ifndef DELETE_HPP
# define DELETE_HPP

/* ************************************************************************** */

#include <iostream>
#include <Response.hpp>

/* ************************************************************************** */

class Delete : public Response {
	private:
	protected:

	public:
		Delete(Request req) : Response(req){
			cout << PURPLE << "Constructing a Delete method" << RESET << endl;
		}

		string toString(){
			return "";
		}
};

/* ************************************************************************** */

#endif /* DELETE_HPP */