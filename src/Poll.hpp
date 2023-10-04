#ifndef POLL_H
#define POLL_H

#include "using.hpp"
#include <poll.h>

#ifdef WDEBUG
# include <cstdlib>
#endif /* WDEBUG */

typedef enum {
	LISTENER,
	READ,
	WRITE,
} PollType;

class Poll
{
private:
public:
	PollType type;
	pollfd poll;
	string response;
	string id;

	Poll(PollType type, pollfd poll, string response);
	~Poll();
};

#endif /* POLL_H */
