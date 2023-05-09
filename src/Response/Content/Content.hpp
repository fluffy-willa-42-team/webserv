#ifndef CONTENT_HPP
# define CONTENT_HPP

/* ************************************************************************** */

#include <iostream>
#include <using.hpp>

/* ************************************************************************** */

class Content {
	protected:
		string path;
	public:
		Content(const string& path): path(path){}
		virtual ~Content() = 0;
};

/* ************************************************************************** */

#endif /* CONTENT_HPP */