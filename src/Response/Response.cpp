#include "Response.hpp"

Response::Response(const Request& req): req(req){
	content = content_factory(req.path);
}

Response::~Response(){
	delete content;
}

std::ostream& operator<<(std::ostream& out, const Response& res){
	out << res.toString();
	return out;
}