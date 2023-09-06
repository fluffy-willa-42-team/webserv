#ifndef REQUEST_VALIDATION_HPP
# define REQUEST_VALIDATION_HPP

/* ************************************************************************** */

#include "webserv.hpp"

/* ************************************************************************** */

typedef enum {
	SUCCESS,
	BAD_REQUEST,
	NOT_ALLOWED,
}	e_validation_status;

/* ************************************************************************** */

e_validation_status is_method_valid(const string& method);
bool is_path_valid(const string& path);
e_validation_status is_protocol_valid(const string& protocol);

/* ************************************************************************** */

#endif /* REQUEST_VALIDATION_HPP */