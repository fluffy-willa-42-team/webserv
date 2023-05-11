#include "Response.hpp"

Response::Response(const Request& req): request(req){
	content = content_factory(request.path);
}

Response::~Response(){
	delete content;
}

std::ostream& operator<<(std::ostream& out, const Response& res){
	out << res.toString();
	return out;
}