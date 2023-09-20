#include "debug.hpp"

webDebugTrace::webDebugTrace(const level_t level, const std::string file, const int line)
{
#ifdef WDEBUG
	this->level = level;

	if (level < WDEBUG)
		return;

	const string level_str[] = {
		"DEBUG",
		"INFO",
		"WARN",
		"ERROR"
	};
	const string level_color[] = {"\033[1;32m", "\033[1;33m", "\033[1;34m", "\033[1;31m"};

	cout << level_color[level] << "[" << level_str[level] << "] " << file << ":" << line << "\033[0m" << " : ";
#endif
#ifndef WDEBUG
	(void)level;
	(void)file;
	(void)line;
#endif
}

webDebugTrace::~webDebugTrace() {
#ifdef WDEBUG
	if (level < WDEBUG)
		return;
	std::cout << std::endl;
#endif
}