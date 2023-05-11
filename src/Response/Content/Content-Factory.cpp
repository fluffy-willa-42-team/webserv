#include "File.hpp"
#include "CGI.hpp"
#include "Redirect.hpp"
#include "Config.hpp"

/**
 * @brief Determine what that of content the response should sent based on the
 * path and the config
 * 
 * @param path 
 * @return Content* 
 */
Content* content_factory(const string& path, const Config& config){
	(void) config;
	//TODO
	// if (is_redirect)
	// 	return new RedirectContent(path);
	// if (is_cgi)
	// 	return new CGIContent(path);

	return new FileContent(path);
}
