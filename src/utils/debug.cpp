#include "debug.hpp"

ostream& debug_utils(const level_t level, const string file, const int line) {
	static NullStream nullStream;
	#ifdef WDEBUG
		if (level < WDEBUG)
			return nullStream;
		cerr << level_color[level] << "[" << level_str[level] << "] " << file << ":" << line << " : " << RESET;
		return cerr;
	#else
		(void) level;
		(void) file;
		(void) line;
		return nullStream;
	#endif
}