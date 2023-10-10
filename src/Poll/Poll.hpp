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
	EXE_CGI,
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
	Request	req;

	Poll(PollType type, pollfd poll, string response);
	~Poll();
};

#endif /* POLL_H */
