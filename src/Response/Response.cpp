#include "Response.hpp"

Response::Response(const Request& req): request(req){
	content = content_factory(req.path);
}

Response::~Response(){
	delete content;
}
