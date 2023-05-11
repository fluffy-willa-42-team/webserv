#ifndef WEBSERV_HPP
# define WEBSERV_HPP

/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <map>

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

# define PROTOCOL "HTTP/1.1"

/* ************************************************************************** */

using std::pair;
using std::map;
using std::string;
using std::stringstream;
using std::endl;
using std::cout;
using std::runtime_error;

/* ************************************************************************** */

#endif /* WEBSERV_HPP */