#ifndef RESPONSEHEADER_HPP
# define RESPONSEHEADER_HPP

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

class ResponseHeader {
	private:
	protected:
	public:
		ResponseHeader();
		~ResponseHeader();
		ResponseHeader(const ResponseHeader& other);
		const ResponseHeader& operator=(const ResponseHeader& other);
};

/* ************************************************************************** */

#endif /* RESPONSEHEADER_HPP */