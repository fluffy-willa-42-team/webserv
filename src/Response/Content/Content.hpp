#ifndef CONTENT_HPP
# define CONTENT_HPP

/* ************************************************************************** */

#include <webserv.hpp>
#include <Config.hpp>

/* ************************************************************************** */

class Content {
	protected:
		string path;
		string type;
		string data;
	public:
		bool special_code;

		Content(const string& path): path(path), type(""), special_code(false){}
		virtual ~Content() = 0;

		virtual string toString() const = 0;

		friend std::ostream& operator<<(std::ostream& out, const Content& content);
};

Content* content_factory(const string& path, const Config& config);

/* ************************************************************************** */

#endif /* CONTENT_HPP */