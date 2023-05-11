#ifndef FILE_CONTENT_HPP
# define FILE_CONTENT_HPP

/* ************************************************************************** */

#include <iostream>
#include <webserv.hpp>
#include <Content.hpp>

/* ************************************************************************** */

class FileContent : public Content {
	private:
	public:
		FileContent(const string& path);
		~FileContent();

		virtual string toString() const;
};

/* ************************************************************************** */

#endif /* FILE_CONTENT_HPP */