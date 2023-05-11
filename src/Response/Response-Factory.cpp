#include "Config.hpp"

#include "Get.hpp"
#include "Post.hpp"
#include "Delete.hpp"

Response* response_factory(const Request& req, const Config& config){
	if (req.method == "GET")
		return new Get(req, config);
	if (req.method == "POST")
		return new Post(req, config);
	if (req.method == "DELETE")
		return new Delete(req, config);
	throw Response::InvalidResponse("Invalid Method");
}
