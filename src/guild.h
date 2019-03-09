#ifndef GUILD_H
#define GUILD_H
#include <stdint.h>
#include "vector.h"

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
vec_t *get_guild_channels(uint64_t guild_id);
channel_t *create_guild_channel(uint64_t guild_id, channel_t *channel);
int modify_channel_position(uint64_t guild_id, uint64_t channel_id,
		int position);
vec_t *list_guild_members(uint64_t guild_id, uint16_t limit, uint64_t after);
int add_guild_member(uint64_t guild_id, uint64_t user_id, char *oauth_token,
		char *nick, vec_t *roles, int mute, int deaf);
int modfiy_guild_member(uint64_t guild_id, uint64_t user_id, vec_t *roles,
		int mute, int deaf, uint64_t channel_id);
int modify_self_nick(uint64_t guild_id, char *nick);
int add_member_role(uint64_t guild_id, uint64_t user_id, uint64_t role_id);
int remove_member_role(uint64_t guild_id, uint64_t user_id, uint64_t role_id);
int kick_member(uint64_t guild_id, uint64_t user_id);
vec_t *get_bans(uint64_t guild_id);
int ban_member(uint64_t guild_id, uint64_t user_id, int delete_msg_days,
		char *reason);
int unban_member(uint64_t guild_id, uint64_t user_id);
vec_t *get_guild_roles(uint64_t guild_id);
role_t *create_role(uint64_t guild_id, role_t *role);
vec_t *modify_role_pos(uint64_t guild_id, uint64_t role_id, int pos);
role_t *modify_role(uint64_t guild_id, role_t *role);
int delete_role(uint64_t guild_id, uint64_t role_id);
uint16_t get_prune_count(uint64_t guild_id, uint8_t days);
uint16_t begin_guild_prune(uint64_t guild_id, uint8_t days, int compute_prune_count);
vec_t *get_guild_voice_regions(uint64_t guild_id);
vec_t *get_guild_invites(uint64_t guild_id);
vec_t *get_guild_integrations(uint64_t guild_id);
int create_guild_intergation(uint64_t guild_id, char *type, uint64_t id);
int modify_guild_integration(uint64_t guild_id, uint64_t id, int exp_behavior,
		int exp_grace_per, int enable_emoticons);
int delete_guild_intergration(uint64_t guild_id, uint64_t id);
int sync_guild_integration(uint64_t guild_id, uint64_t id);
guildembed_t *get_guild_embed(uint64_t guild_id);
guildembed_t *modify_guild_embed(uint64_t guild_id, guildembed_t *embed);
invite_t *get_guild_vanity_url(uint64_t guild_id);
//void get_guild_widget_image(uint64_t guild_id);
#endif 
