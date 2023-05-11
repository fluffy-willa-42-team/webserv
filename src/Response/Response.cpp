#include "Response.hpp"

Response::Response(const Request& req, const Config& config):
	config(config),
	req(req),
	code(200),
	send_content_or_code_msg(false)
{
	content = content_factory(req.path, config);
}

Response::~Response(){
	delete content;
}

std::ostream& operator<<(std::ostream& out, const Response& res){
	out << res.toString();
	return out;
}