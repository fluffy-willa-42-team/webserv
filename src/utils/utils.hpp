#ifndef UTILS_HPP
# define UTILS_HPP

/* ************************************************************************** */

#include "webserv.hpp"

/* ************************************************************************** */

string readFileIntoString(const string& path);
void replace_string(string& input, const string& pattern_in, const string& pattern_out);
vector<string> split(const string& s, const string& delimiter);
vector<string> splitFirst(const string& s, const string& delimiter);
void removeCarriageReturn(string& line);

/* ************************************************************************** */

#endif /* UTILS_HPP */