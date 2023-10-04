#ifndef HTTP_HPP
# define HTTP_HPP

/******************************************************************************/

#include "webserv.hpp"
#include "utils.hpp"
#include "Config.hpp"
#include "Listener.hpp"
#include "request_validation.hpp"

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
	string	method;
	string	path;
	string	param;
	Headers	headers;
	string	body;
}	Request;


/******************************************************************************/

string error(u_int32_t code, const string& message = "");
string error_serv(const Server& serv, u_int32_t code, const string& message = "");

const Server& find_server(const Config& config, Headers headers);
const Location& find_location(const Server& serv, const string& req_path_param);

const string http(const int fd, const Config& config, const Env& env);

/******************************************************************************/

#endif /* HTTP_HPP */