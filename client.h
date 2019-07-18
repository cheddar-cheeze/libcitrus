#ifndef client_h
#define client_h

#include <jansson.h>

#include "user.h"

struct client
{
	struct user *self;
	char *token;
	char *user_agent;
	char *proxy;
};

struct http_response
{
	char *body;
	long code;
};

enum method
{
	GET,
	POST,
	PUT,
	DELETE,
};


long http_request(struct client *client, const char *url, int use_auth, char **response_buff, enum method method, const char *post_fields);
#endif
