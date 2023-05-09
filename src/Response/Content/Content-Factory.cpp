#include "File.hpp"
#include "CGI.hpp"
#include "Redirect.hpp"


static map<string, string> extention_map;

void populate_extention_map(map<string, string>& extention_map);

/**
 * @brief Determine what that of content the response should sent based on the
 * path and the config
 * 
 * @param path 
 * @return Content* 
 */
Content* content_factory(const string& path){
	if (extention_map.empty())
		populate_extention_map(extention_map);
	
	//TODO
	// if (is_redirect)
	// 	return new RedirectContent(path);
	// if (is_cgi)
	// 	return new CGIContent(path);

	return new FileContent(path);
}
