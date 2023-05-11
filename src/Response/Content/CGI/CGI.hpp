#ifndef CGI_CONTENT_HPP
# define CGI_CONTENT_HPP

/* ************************************************************************** */

#include <iostream>
#include <webserv.hpp>
#include <Content.hpp>

/* ************************************************************************** */

class CGIContent : public Content {
	private:
	public:
		CGIContent(const string& path);
		~CGIContent();

		virtual string toString() const;
};

/* ************************************************************************** */

#endif /* CGI_CONTENT_HPP */