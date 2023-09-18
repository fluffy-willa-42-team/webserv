#ifndef UTILS_HPP
# define UTILS_HPP

/* ************************************************************************** */

#include "webserv.hpp"

/* ************************************************************************** */

string readFileIntoString(const string& path);
void replace_string(string& input, const string& pattern_in, const string& pattern_out);
vector<string> split(const string& s, const string& delimiter);
vector<string> splitFirst(const string& s, const string& delimiter);
vector<string> splitStringByWhitespace(const string& input);
bool removeCarriageReturn(string& line);
bool map_has_key(const map<string, string>& i_map, string key);
u_int32_t stringToNumber(const string& str);

/* ************************************************************************** */

#endif /* UTILS_HPP */