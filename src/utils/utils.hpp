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
bool isPositiveInteger(const string& str);
u_int32_t stringToNumber(const string& str);
string numberToString(u_int32_t number);

/* ************************************************************************** */

bool isFileReadable(const string& filepath);
bool isFileExecutable(const std::string& filepath);
bool doesFolderExists(const string& folderPath);
string mergeFilePaths(const string& base, const string& path);

/* ************************************************************************** */

template<typename T1, typename T2>
bool map_has_key(const map<T1, T2>& i_map, const T1& key){
	typename map<T1, T2>::const_iterator it = i_map.find(key);
	return (it != i_map.end());
}

/* ************************************************************************** */

#endif /* UTILS_HPP */