#ifndef FILE_CONTENT_HPP
# define FILE_CONTENT_HPP

/* ************************************************************************** */

#include <webserv.hpp>
#include <Content.hpp>

/* ************************************************************************** */

class FileContent : public Content {
	private:
	public:
		FileContent(const string& path);
		~FileContent();

		virtual string toString() const;

		class FileNotFound : public std::exception {
			public:
				string message;
				FileNotFound(): 						message("File Not Found"){}
				FileNotFound(const string& message): 	message("File Not Found"){ this->message += ": " + message; }
				~FileNotFound() throw() {}
				virtual const char* what() const throw() { return message.c_str(); }
		};
};

/* ************************************************************************** */

#endif /* FILE_CONTENT_HPP */