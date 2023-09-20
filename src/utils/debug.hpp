#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

typedef enum level_e {
	DEBUG,
	INFO,
	WARN,
	ERROR
} level_t;

#define DEBUG_() webDebugTrace(DEBUG, __FILE__, __LINE__)
#define DEBUG_INFO_() webDebugTrace(INFO, __FILE__, __LINE__)
#define DEBUG_WARN_() webDebugTrace(WARN, __FILE__, __LINE__)
#define DEBUG_ERROR_() webDebugTrace(ERROR, __FILE__, __LINE__)

class webDebugTrace
{
public:
	level_t level;
	webDebugTrace(const level_t level, const std::string file, const int line);

	template <class T>
	webDebugTrace& operator<<(const T &v)
	{
	#ifdef WDEBUG
		if (level < WDEBUG)
			return *this;

		const string level_str[] = {
			"DEBUG",
			"INFO",
			"WARN",
			"ERROR"
		};
		const string level_color[] = {"\033[1;32m", "\033[1;33m", "\033[1;34m", "\033[1;31m"};

		std::cout << level_color[this->level] << v;
	#endif
	#ifndef WDEBUG
		(void)v;
	#endif

		return *this;
	}

	~webDebugTrace();
};

#endif /* DEBUG_H */
