#ifndef POLL_H
#define POLL_H

#include "using.hpp"
#include <poll.h>
#include "http.hpp"

#ifdef WDEBUG
# include <cstdlib>
#endif /* WDEBUG */

typedef enum {
	LISTENER,
	READ_HEAD,
	READ_BODY,
	WRITE,
} PollType;

class Poll
{
private:
public:
	PollType type;
	pollfd poll;
	string id;
	Request	req;

	Poll(PollType type, pollfd poll);
	~Poll();
};

#endif /* POLL_H */
