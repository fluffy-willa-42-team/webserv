#ifndef CONTENT_HPP
# define CONTENT_HPP

/* ************************************************************************** */

#include <webserv.hpp>
#include <Config.hpp>

/* ************************************************************************** */

class Content {
	protected:
		string path;	// Path to content
		string type;	// 
		string data;	// Data after the f
		int    code;	// Code special
	public:
		bool special_code;

		Content(const string& path): path(path), type(""), code(0), special_code(false){}
		virtual ~Content() = 0;

		int getSpecialCode() const { return code; }
		void add_special_code(int code){
			special_code = true;
			this->code = code;
		}

		virtual string toString() const = 0;

		friend std::ostream& operator<<(std::ostream& out, const Content& content);
};

Content* content_factory(const string& path, const Config& config);

/* ************************************************************************** */

#endif /* CONTENT_HPP */