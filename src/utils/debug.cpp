#include "debug.hpp"

webDebugTrace::webDebugTrace(const level_t level, const string file, const int line)
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
		const string level_color[] = {GREEN, YELLOW, BLUE, RED};

		cout << level_color[level] << "[" << level_str[level] << "] " << file << ":" << line << RESET << " : ";
	#endif
	#ifndef WDEBUG
		(void) level;
		(void) file;
		(void) line;
	#endif
}

webDebugTrace::~webDebugTrace() {
#ifdef WDEBUG
	if (level < WDEBUG)
		return;
	std::cout << std::endl;
#endif
}