#ifndef RESPONSE_HPP
# define RESPONSE_HPP

/******************************************************************************/

#include "http.hpp"

/******************************************************************************/

string get_response(u_int32_t code, Headers headers, string body = "");

string get_file_res(const string& file_path, bool download = false);
string get_autoindex(const string& req_path, const string& file_path);
string redirect(u_int32_t code, const string& path);
string error(u_int32_t code, const string& message);

/******************************************************************************/

#endif /* RESPONSE_HPP */