#include "File.hpp"
#include "CGI.hpp"

/**
 * @brief Determine what that of content the response should sent based on the
 * path and the config
 * 
 * @param path 
 * @return Content* 
 */
Content* content_factory(const string& path){
	return new FileContent(path);
}