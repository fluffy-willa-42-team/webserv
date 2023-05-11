#ifndef CONTENT_HPP
# define CONTENT_HPP

/* ************************************************************************** */

#include <iostream>
#include <webserv.hpp>

/* ************************************************************************** */

class Content {
	protected:
		string path;
		string type;
		size_t length;
	public:
		bool special_code;

		Content(const string& path): path(path), type(""), length(0), special_code(false){}
		virtual ~Content() = 0;

		virtual string toString() const = 0;

		friend std::ostream& operator<<(std::ostream& out, const Content& content);
};

Content* content_factory(const string& path);

/* ************************************************************************** */

#endif /* CONTENT_HPP */