#include "debug.hpp"

static const string level_str[]	= {"DEBUG", "INFO ", "WARN ", "ERROR"};
static const string level_color[] = {GREEN, CYAN, BLUE, RED};

std::ostream& debug_utils(const level_t level, const string file, const int line){
	cout << level_color[level] << "[" << level_str[level] << "] " << file << ":" << line << " : " << RESET;
	return cout;
}
