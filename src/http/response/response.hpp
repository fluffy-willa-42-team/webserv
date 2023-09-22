#ifndef RESPONSE_HPP
# define RESPONSE_HPP

/******************************************************************************/

#include "http.hpp"

/******************************************************************************/

string get_response(u_int32_t code, map<string, string> headers, string body = "");

string redirect(u_int32_t code, const string& path);
string error(u_int32_t code, const string& message);

/******************************************************************************/

#endif /* RESPONSE_HPP */