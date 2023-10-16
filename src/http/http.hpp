#ifndef HTTP_HPP
# define HTTP_HPP

/******************************************************************************/

#include "webserv.hpp"
#include "utils.hpp"
#include "Config.hpp"
#include "Listener.hpp"
#include "request_validation.hpp"

class Poll;
/******************************************************************************/

typedef map<string, string> Headers;

typedef enum {
	AINDEX_FILE,
	AINDEX_FOLDER,
} AutoindexValue;



typedef struct {
	AutoindexValue type;
	string path;
	string name;
	off_t fileSize;
} AutoindexInput;

typedef struct {
	string		raw;

	string		method;
	string		path;
	string		param;
	Headers		headers;
	string		body;
	u_int32_t	content_length;
	
	string		response;
	
	Location	loc;
	Server		serv;
}	Request;


/******************************************************************************/

string error(u_int32_t code, const string& message = "");
string error_serv(const Server& serv, u_int32_t code, const string& message = "");

const Server& find_server(const Config& config, Headers headers);
const Location& find_location(const Server& serv, const string& req_method, const string& req_path, u_int32_t& err_code, string& err_message);

void read_header(Poll &poll);
void parse_header(const Config& config, Request& req);
void read_body(Poll &poll);

void execute_request(const Env& env, Request& req);
/******************************************************************************/

#endif /* HTTP_HPP */