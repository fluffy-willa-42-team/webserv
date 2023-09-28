#ifndef UTILS_HPP
# define UTILS_HPP

/* ************************************************************************** */

#include "webserv.hpp"

/* ************************************************************************** */

e_status readFileIntoString(string path, string& destination);
void replace_string(string& input, const string& pattern_in, const string& pattern_out);
vector<string> split(const string& s, const string& delimiter);
vector<string> splitFirst(const string& s, const string& delimiter);
vector<string> splitStringByWhitespace(const string& input);
bool removeCarriageReturn(string& line);
bool isPositiveInteger(const string& str);
u_int32_t stringToNumber(const string& str);
string numberToString(u_int32_t number);
bool startsWith(const string& input, const string& prefix);
bool endsWith(const string& input, const string& suffix);

/* ************************************************************************** */

bool isFileReadable(const string& filepath);
bool isFileExecutable(const string& filepath);
bool doesFolderExists(const string& folderPath);
string mergeFilePaths(const string& base, const string& path);

/* ************************************************************************** */

char** createCopy(const vector<string>& vec);
void freeCopy(const vector<string>& vec, char** copy);

/* ************************************************************************** */

template<typename T1, typename T2>
bool map_has_key(const map<T1, T2>& i_map, const T1& key){
	typename map<T1, T2>::const_iterator it = i_map.find(key);
	return (it != i_map.end());
}

/* ************************************************************************** */

#endif /* UTILS_HPP */