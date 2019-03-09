#ifndef USER_H
#define USER_H
#include <stdint.h>
#include "vector.h"

typedef struct
{
	uint64_t id;
	char *username;
	char *discrim;
	char *avatar;
	int is_bot;
	int is_mfa;
	char *locale;
	int is_verified;
	char *email;
	//flags ???
	int premium;
} user_t;

user_t *get_current_user(void);
user_t *get_user(uint64_t id);
user_t *modify_current_user(char *username); //not complete function as thier is some undocumented params
vec_t *get_current_user_guilds(void);
int leave_guild(uint64_t guild_id);
vec_t *get_user_dms(void);
dmchannel_t *create_dm(uint64_t recipient_id);
dmchannel_t *create_group_dm(vec_t *access_tokens); //poorly documented api call
#endif
