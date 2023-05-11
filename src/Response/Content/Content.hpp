#ifndef CONTENT_HPP
# define CONTENT_HPP

/* ************************************************************************** */

#include <iostream>
#include <webserv.hpp>

/* ************************************************************************** */

class Content {
	protected:
		string path;
	public:
		Content(const string& path): path(path){}
		virtual ~Content() = 0;
};

Content* content_factory(const string& path);

/* ************************************************************************** */

#endif /* CONTENT_HPP */