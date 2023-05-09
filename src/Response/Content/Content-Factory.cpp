#include "File.hpp"
#include "CGI.hpp"

Content* content_factory(const string& path){
	return new FileContent(path);
}