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

/******************************************************************************/

string error(u_int32_t code, const string& message = "");

const Server& find_Server(const Config& config, Headers headers);

const string http(const string& req, Listener& listener, const Config& config);

/******************************************************************************/

#endif /* HTTP_HPP */