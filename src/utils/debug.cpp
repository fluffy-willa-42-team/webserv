#include "debug.hpp"

ostream& debug_utils(const level_t level, const string file, const int line) {
	static NullStream nullStream;
	#ifdef WDEBUG
		if (level < WDEBUG)
			return nullStream;
		cout << level_color[level] << "[" << level_str[level] << "] " << file << ":" << line << " : " << RESET;
		return cout;
	#else
		(void) level;
		(void) file;
		(void) line;
		return nullStream;
	#endif
}