#ifndef invite_h
#define invite_h

#include <stdbool.h>

struct invite 
{
	const char *code;
	struct guild *guild;
	struct channel *channel;
	unsigned int apprx_online;
	unsigned int apprx_total;
};

struct invite_meta
{
	struct user *inviter;
	unsigned int uses;
	unsigned int max_uses;
	unsigned int max_age;
	bool temp;
	struct tm *created_at;
	bool revoked;
};

struct invite *get_invite(char *code);
struct invite *delete_invite(char *code);
#endif
