#ifndef EMOJI_H
#define EMOJI_H
#include <stdint.h>
#include "util.h"

typedef struct
{
	uint64_t id;
	char *name;
	uint64_t *roles;
	user *user;
	int req_colons;
	int managed;
	int animated;
} emoji_t;

vec_t *list_guild_emojis(uint64_t guild_id);

emoji_t *get_guild_emoji(uint64_t guild_id, uint64_t emoji_id);

int create_guild_emojie(uint64_t guild_id, char *name, char *image, vec_t *roles);

int modify_guild_emoji(uint64_t guild_id, uint64_t emoji_id char *name, vec_t *roles);

int delete_guild_emoji(uint64_t guild_id, uint64_t emoji_id);

#endif
