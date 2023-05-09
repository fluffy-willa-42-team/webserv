#ifndef FILE_CONTENT_HPP
# define FILE_CONTENT_HPP

/* ************************************************************************** */

#include <iostream>
#include <using.hpp>
#include <Content.hpp>

/* ************************************************************************** */

class FileContent : public Content {
	private:
	public:
		FileContent(const string& path) : Content(path){
			cout << PURPLE << "Constructing a File Content" << RESET << endl;
		}
		~FileContent(){};
};

/* ************************************************************************** */

#endif /* FILE_CONTENT_HPP */