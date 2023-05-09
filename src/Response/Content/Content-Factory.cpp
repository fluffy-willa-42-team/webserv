#include "File.hpp"
#include "CGI.hpp"

Content* content_factory(const string& path){
	Content* tmp = new FileContent(path);
	return tmp;
}