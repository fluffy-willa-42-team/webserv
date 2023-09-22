#ifndef WEBSERV_HPP
# define WEBSERV_HPP

/* ************************************************************************** */

#include "debug.hpp"
#include "using.hpp"

/* ************************************************************************** */

# define PROTOCOL 				"HTTP/1.1"
# define SERVER_VERSION			"webserv/1.0"
# define DEFAULT_CONFIG_PATH	"./conf/default.conf"

/* ************************************************************************** */

# define HEADER_CONTENT_LENGTH	"Content-Length"
# define HEADER_ACCEPT			"Accept"
# define HEADER_ACCEPT_ENCODING	"Accept-Encoding"
# define HEADER_ACCEPT_LANGUAGE	"Accept-Language"
# define HEADER_HOST			"Host"
# define HEADER_REDIRECT		"Location"

/* ************************************************************************** */

typedef enum {
	S_CONTINUE	= 0b00001,
	S_STOP		= 0b00010,
	S_PASS		= 0b00100,
	S_END		= 0b01000,
	S_ERROR		= 0b10000,
}	e_status;

/* ************************************************************************** */

#endif /* WEBSERV_HPP */