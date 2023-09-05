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

# define PROTOCOL 		"HTTP/1.1"
# define SERVER_VERSION "webserv/1.0"

/* ************************************************************************** */

using std::pair;
using std::map;
using std::vector;
using std::string;
using std::stringstream;
using std::endl;
using std::cout;
using std::cerr;
using std::runtime_error;
using std::ifstream;
using std::memset;
using std::exception;

/* ************************************************************************** */

#define CODES \
    { \
        {400, "Bad Request"}, \
        {401, "Unauthorized"}, \
        {402, "Payment Required"}, \
        {403, "Forbidden"}, \
        {404, "Not Found"}, \
        {405, "Method Not Allowed"}, \
        {406, "Not Acceptable"}, \
        {407, "Proxy Authentication Required"}, \
        {408, "Request Timeout"}, \
        {409, "Conflict"}, \
        {410, "Gone"}, \
        {411, "Length Required"}, \
        {412, "Precondition Failed"}, \
        {413, "Payload Too Large"}, \
        {414, "URI Too Long"}, \
        {415, "Unsupported Media Type"}, \
        {416, "Range Not Satisfiable"}, \
        {417, "Expectation Failed"}, \
        {418, "I'm a teapot"}, \
        {421, "Misdirected Request"}, \
        {422, "Unprocessable Entity"}, \
        {423, "Locked"}, \
        {424, "Failed Dependency"}, \
        {425, "Too Early (RFC 8470)"}, \
        {426, "Upgrade Required"}, \
        {428, "Precondition Required"}, \
        {429, "Too Many Requests"}, \
        {431, "Request Header Fields Too Large"}, \
        {451, "Unavailable For Legal Reasons"}, \
        {500, "Internal Server Error"}, \
        {501, "Not Implemented"}, \
        {502, "Bad Gateway"}, \
        {503, "Service Unavailable"}, \
        {504, "Gateway Timeout"}, \
        {505, "HTTP Version Not Supported"}, \
        {506, "Variant Also Negotiats"}, \
        {507, "Insufficient Storage"}, \
        {508, "Loop Detected"}, \
        {510, "Not Extended"}, \
        {511, "Network Authentication Required"} \
    }

/* ************************************************************************** */

#endif /* WEBSERV_HPP */