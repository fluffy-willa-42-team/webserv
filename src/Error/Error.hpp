#ifndef ERROR_HPP
# define ERROR_HPP

/******************************************************************************/

#include "webserv.hpp"

/******************************************************************************/

class Error {
	private:
		u_int32_t code;
		string message;
		string description;

	public:
		Error();
		Error(u_int32_t code, string message, string description);
		~Error();
		const Error& operator=(const Error& other);

		const string http();
};

/******************************************************************************/

#endif /* ERROR_HPP */