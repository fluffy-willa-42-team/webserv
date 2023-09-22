#ifndef DEBUG_H
# define DEBUG_H

/******************************************************************************/

# include <iostream>
# include <string>
# include <sstream>

# define RESET	"\e[0m"

# define BLACK	"\e[0;30m"
# define RED	"\e[0;31m"
# define GREEN	"\e[0;32m"
# define YELLOW	"\e[0;33m"
# define BLUE	"\e[0;34m"
# define PURPLE	"\e[0;35m"
# define CYAN	"\e[0;36m"
# define WHITE	"\e[0;37m"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

/******************************************************************************/

typedef enum level_e {
	DEBUG,
	INFO,
	WARN,
	ERROR
} level_t;

/******************************************************************************/

#define DEBUG_() webDebugTrace(DEBUG, __FILE__, __LINE__)
#define DEBUG_INFO_() webDebugTrace(INFO, __FILE__, __LINE__)
#define DEBUG_WARN_() webDebugTrace(WARN, __FILE__, __LINE__)
#define DEBUG_ERROR_() webDebugTrace(ERROR, __FILE__, __LINE__)

class webDebugTrace
{
public:
	level_t level;
	webDebugTrace(const level_t level, const string file, const int line);

	template <class T>
	webDebugTrace& operator<<(const T &v)
	{
		#ifdef WDEBUG
			if (level < WDEBUG)
				return *this;

			const string level_str[]	= {"DEBUG", "INFO", "WARN", "ERROR"};
			const string level_color[]	= {GREEN, YELLOW, BLUE, RED};
			cout << level_color[this->level] << RESET << v;
		#endif
		#ifndef WDEBUG
			(void) v;
		#endif

		return *this;
	}

	~webDebugTrace();
};

#endif /* DEBUG_H */
