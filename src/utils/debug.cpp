#include "debug.hpp"

std::ostream& debug_utils(const level_t level, const string file, const int line) {
	#ifdef WDEBUG
		cout << level_color[level] << "[" << level_str[level] << "] " << file << ":" << line << " : " << "\033[0m";
		return cout;
	#else
		static NullStream nullStream;
		(void) level;
		(void) file;
		(void) line;
		return nullStream;
	#endif
}