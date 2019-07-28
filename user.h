#ifndef user_h
#define user_h

#include <stdbool.h>
#include "guild.h"

struct user
{
	unsigned long long id;
	const char *username;
	const char *discriminator;
	const char *avatar;
	bool bot;
	bool mfa_enabled;
	const char *locale;
	bool verified;
	const char *email;
	unsigned int flags;
	bool premium;
};

struct user *get_current_user(void);
struct user *get_user(unsigned long long id);
struct user *modify_current_user(char *username); //not complete function as thier is some undocumented params
struct guild **get_current_user_guilds(void);
int leave_guild(unsigned long long guild_id);
struct dmchannel get_user_dms(void);
struct dmchannel *create_dm(unsigned char recipient_id);
struct dmchannel *create_group_dm(void); //poorly documented api call
#endif
