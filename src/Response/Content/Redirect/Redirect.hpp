#ifndef REDIRECT_CONTENT_HPP
# define REDIRECT_CONTENT_HPP

/* ************************************************************************** */

#include <iostream>
#include <webserv.hpp>
#include <Content.hpp>

/* ************************************************************************** */

class RedirectContent : public Content {
	private:
	public:
		RedirectContent(const string& path);
		~RedirectContent();

		virtual string toString() const;
};

/* ************************************************************************** */

#endif /* REDIRECT_CONTENT_HPP */