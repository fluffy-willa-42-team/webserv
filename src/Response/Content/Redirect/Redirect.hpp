#ifndef REDIRECT_CONTENT_HPP
# define REDIRECT_CONTENT_HPP

/* ************************************************************************** */

#include <iostream>
#include <using.hpp>
#include <Content.hpp>

/* ************************************************************************** */

class RedirectContent : public Content {
	private:
	public:
		RedirectContent(const string& path) : Content(path){
			cout << PURPLE << "Constructing a Redirect Content" << RESET << endl;
		}
		~RedirectContent(){};
};

/* ************************************************************************** */

#endif /* REDIRECT_CONTENT_HPP */