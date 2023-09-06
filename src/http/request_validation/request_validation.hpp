#ifndef REQUEST_VALIDATION_HPP
# define REQUEST_VALIDATION_HPP

/* ************************************************************************** */

#include "webserv.hpp"

/* ************************************************************************** */

bool is_method_valid(const string& method);
bool is_path_valid(const string& path);
bool is_protocol_valid(const string& path);

/* ************************************************************************** */

#endif /* REQUEST_VALIDATION_HPP */