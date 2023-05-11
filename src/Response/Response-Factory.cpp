#include "Get.hpp"
#include "Post.hpp"
#include "Delete.hpp"

Response* response_factory(Request req){
	if (req.method == "GET")
		return new Get(req);
	if (req.method == "POST")
		return new Post(req);
	if (req.method == "POST")
		return new Post(req);
	throw Response::InvalidResponse("Invalid Method");
}
