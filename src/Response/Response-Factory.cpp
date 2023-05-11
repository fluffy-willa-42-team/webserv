#include "Get.hpp"
#include "Post.hpp"
#include "Delete.hpp"

Response* response_factory(const Request& req){
	if (req.method == "GET"){
		return new Get(req);
	}
	if (req.method == "POST")
		return new Post(req);
	if (req.method == "DELETE")
		return new Delete(req);
	throw Response::InvalidResponse("Invalid Method");
}
