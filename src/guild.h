#ifndef GUILD_H
#define GUILD_H
#include <stdint.h>
#include "util.h"

typedef struct
{
	uint64_t id;
	char *name;
	char *icon;
	char *splash;
	int self_is_owner;
	uint64_t owner_id;
	int permissions;
	char *region;
	uint64_t afk_channel_id;
	uint16_t afk_timeout;
	int embed_enabled;
	uint64_t embed_channel_id;
	int verification_level;
	int notification_level;
	int explicit_filter_level;
	vec_t *roles;
	vec_t *emojis;
	vec_t *features;
	int mfa_level;
	uint64_t application_id;
	int widget_enabled;
	uint64_t system_channel_id;
	//joined at, shitty timestamp
	int large;
	int unavailible;
	uint16_t member_count;
	vec_t *voice_states;
	vec_t *members;
	vec_t *channels;
	vec_t *presences;
} guild_t;

typedef enum
{
	ALL_MESSAGES,
	ONLY_MENTIONS
} notification_level;

typedef enum
{
	DISABLED,
	MEMBER_WITHOUT_ROLES,
	ALL_MEMBERS
} explicit_filter_level;

typedef enum
{
	NONE,
	ELEVATED
} mfa_level;

typedef enum
{
	NONE,
	LOW,
	MEDIUM,
	HIGH,
	VERY_HIGH
} verification_level;

typedef struct
{
	int enabled;
	uint64_t channel_id;
} guildembed_t;

typedef struct
{
	user *user;
	char *nick;
	vec_t *roles;
	//shitty timestamp;
	int deaf;
	int mute;
} member_t;

typedef struct
{
	uint64_t id;
	char *name;
	char *type;
	int syncing;
	uint64_t role_id;
	uint16_t expire_behavior;
	uint16_t expire_grace_period;
	user *user;
	//account;
	//shitty iso timestamp;
} integration_t;

typedef struct
{	
	char *id;
	char *name;
} intergrationaccnt_t;

typedef struct 
{
	char *reason;
	user *user;
} ban_t;

guild_t *create_guild(guild_t *guild);

guild_t *get_guild(uint64_t guild_id);

guild_t *modify_guild(guild_t *guild);

int delete_guild(uint64_t guild_id);

#endif 
