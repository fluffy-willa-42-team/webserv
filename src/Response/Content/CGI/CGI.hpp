#ifndef CGI_CONTENT_HPP
# define CGI_CONTENT_HPP

/* ************************************************************************** */

#include <iostream>
#include <using.hpp>
#include <Content.hpp>

/* ************************************************************************** */

class CGIContent : public Content {
	private:
	public:
		CGIContent(const string& path) : Content(path){
			cout << PURPLE << "Constructing a CGI Content" << RESET << endl;
		};
};

/* ************************************************************************** */

#endif /* CGI_CONTENT_HPP */