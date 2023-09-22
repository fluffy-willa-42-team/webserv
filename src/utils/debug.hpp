#ifndef DEBUG_H
# define DEBUG_H

/******************************************************************************/

# include "using.hpp"

/******************************************************************************/

# define RESET	"\e[0m"

# define BLACK	"\e[0;30m"
# define RED	"\e[0;31m"
# define GREEN	"\e[0;32m"
# define YELLOW	"\e[0;33m"
# define BLUE	"\e[0;34m"
# define PURPLE	"\e[0;35m"
# define CYAN	"\e[0;36m"
# define WHITE	"\e[0;37m"

/******************************************************************************/

typedef enum level_e {
	DEBUG,
	INFO,
	WARN,
	ERROR
} level_t;

/******************************************************************************/

#define DEBUG_()		debug_utils(DEBUG, __FILE__, __LINE__)
#define DEBUG_INFO_()	debug_utils(INFO, __FILE__, __LINE__)
#define DEBUG_WARN_()	debug_utils(WARN, __FILE__, __LINE__)
#define DEBUG_ERROR_()	debug_utils(ERROR, __FILE__, __LINE__)

std::ostream& debug_utils(const level_t level, const string file, const int line);

#endif /* DEBUG_H */
