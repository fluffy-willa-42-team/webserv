#ifndef WEBSERV_HPP
# define WEBSERV_HPP

/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <errno.h>

/* ************************************************************************** */

# define RESET	"\e[0m"

# define BLACK	"\e[0;30m"
# define RED	"\e[0;31m"
# define GREEN	"\e[0;32m"
# define YELLOW	"\e[0;33m"
# define BLUE	"\e[0;34m"
# define PURPLE	"\e[0;35m"
# define CYAN	"\e[0;36m"
# define WHITE	"\e[0;37m"

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

/* ************************************************************************** */

using std::string;
using std::pair;
using std::map;
using std::vector;

using std::stringstream;
using std::ifstream;

using std::cout;
using std::endl;
using std::cerr;

using std::memset;
using std::getline;

using std::exception;

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