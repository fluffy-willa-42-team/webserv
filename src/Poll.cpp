#include "Poll.hpp"
#include "debug.hpp"

#ifdef WDEBUG
# include <limits.h>
#endif /* WDEBUG */

Poll::Poll(PollType type, pollfd poll, string response)
: type(type), poll(poll), response(response), id("")
{
#ifdef WDEBUG
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	int len = 10;
	for (int i = 0; i < len; ++i) {
		id += alphanum[rand() % (sizeof(alphanum) - 1)];
	}
	DEBUG_ << "Poll " << id << " created of type " << type << endl;
#endif
}

Poll::~Poll()
{
}