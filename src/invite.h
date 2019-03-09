#ifndef INVITE_H
#define INVITE_H
#include <stdint.h>

typedef struct
{
	char *code;
	guild_t *guild;
	channel_t *channel;
	uint16_t apprx_online;
	uint16_t apprx_total;
} invite_t;

typedef struct
{
	user_t *inviter;
	uint16_t uses;
	uint16_t max_uses;
	uint16_t max_age;
	int temp;
	//shite time format;
	int revoked;
} invitemeta_t;

invite_t *get_invite(char *code);
invite_t *delete_invite(char *code);
#endif
