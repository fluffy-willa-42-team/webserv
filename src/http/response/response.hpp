#ifndef RESPONSE_HPP
# define RESPONSE_HPP

/******************************************************************************/

#include "http.hpp"

/******************************************************************************/

#define AUTOINDEX_FILE				"./src/html/autoindex.html"
#define AUTOINDEX_FILE_FRAG_FILE	"./src/html/autoindex_fragment_file.html"
#define AUTOINDEX_FILE_FRAG_FOLDER	"./src/html/autoindex_fragment_folder.html"
#define ERROR_FILE					"./src/html/error.html"

/******************************************************************************/

extern string raw_autoindex_fragment_file;
extern string raw_autoindex_fragment_folder;
extern string raw_autoindex;
extern string raw_error_file;

extern map<u_int32_t, string> codes_map;
extern map<u_int32_t, string> redirect_codes_map;
extern map<u_int32_t, string> error_codes_map;
extern map<string, u_int32_t> default_codes;

/******************************************************************************/

string get_response(u_int32_t code, Headers headers, string body = "");

string get_file_res(const string& file_path, bool download = false);
string get_autoindex(const string& req_path, const string& file_path);
string redirect(u_int32_t code, const string& path);
string error(u_int32_t code, const string& message);

bool is_file_cgi(const Location& loc, const string& filename, string& cgi_bin);
string cgi(
	const Env& env,
	const Server& serv,
	const Location& loc,
	const string& cgi_bin,
	const string& filepath,
	const string& req_method,
	const string& req_path,
	const string& req_param,
	const string& req_body = ""
);

/******************************************************************************/

#endif /* RESPONSE_HPP */