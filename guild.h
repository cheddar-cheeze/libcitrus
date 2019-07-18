#ifndef guild_h
#define guild_h

#include <time.h>
#include <stdbool.h>

struct guild
{
	unsigned long long id;
	const char *name;
	const char *icon;
	const char *splash;
	bool self_is_owner;
	unsigned long long owner_id;
	int permissions;
	const char *region;
	unsigned long long afk_channel_id;
	unsigned int afk_timeout;
	bool  embed_enabled;
	unsigned long long embed_channel_id;
	unsigned char verification_level;
	unsigned char notification_level;
	unsigned char explicit_filter_level;
	//roles array will be terminated will a null ptr
	size_t role_count;
	struct role **roles;
	size_t emoji_count;
	struct emoji **emojis;
	size_t feature_count;
	struct feature **features;
	unsigned char mfa_level;
	unsigned long long application_id;
	bool widget_enabled;
	unsigned long long system_channel_id;
	struct tm *joined_at;
	bool large;
	bool unavailible;
	size_t member_count;
	size_t voice_state_count;
	struct voice_state **voice_states;
	struct member **members;
	size_t channel_count;
	struct channel **channels;
	size_t presence_count;
	struct presence **presences;
};

enum notification_level
{
	ALL_MESSAGES,
	ONLY_MENTIONS
};

enum filter_level
{
	DISABLED,
	MEMBER_WITHOUT_ROLES,
	ALL_MEMBERS
};

enum mfa_level
{
	NICHT, //suppoed to be none but since none & disabled is taken thats the best nextoption
	ELEVATED
};

enum verification_level
{
	NONE,
	LOW,
	MEDIUM,
	HIGH,
	VERY_HIGH
};

struct guild_embed
{
	unsigned char enabled;
	unsigned long long channel_id;
};

struct member
{
	struct user *user;
	const char *nick;
	size_t role_count;
	unsigned long long *roles;
	struct tm *joined_at;
	struct tm *premium_since;
	bool deaf;
	bool mute;
};

struct integration
{
	unsigned long long id;
	const char *name;
	const char *type;
	bool syncing;
	unsigned long long role_id;
	unsigned int expire_behavior;
	unsigned int expire_grace_period;
	struct user *user;
	struct integration_account *account;
	struct tm *synced_at;
};

struct integration_account
{	
	const char *id;
	const char *name;
};

struct role
{
	unsigned long long id;
	const char *name;
	int color;
	bool hoist;
	int position;
	int permissions;
	bool managed;
	bool mentionable;
};


struct ban
{
	const char *reason;
	struct user *user;
};

struct guild *create_guild(struct guild *guild);
struct guild *get_guild(unsigned long long guild_id);
struct guild *modify_guild(struct guild *mod_guild);
int delete_guild(unsigned long long guild_id);
struct channel *get_guild_channels(unsigned long long guild_id);
struct channel *create_guild_channel(unsigned long long guild_id, struct channel *channel);
int modify_channel_position(unsigned long long guild_id, unsigned long long channel_id, int position);
struct member *list_guild_members(unsigned long long guild_id, unsigned int limit, unsigned long long after);
int add_guild_member(unsigned long long  guild_id, unsigned long long user_id, char *oauth_token, char *nick, struct role *roles, unsigned char mute, unsigned char deaf);
int modfiy_guild_member(unsigned long long guild_id, unsigned long long  user_id, struct role *roles, unsigned char  mute, unsigned char deaf, unsigned long long channel_id);
int modify_self_nick(unsigned long long guild_id, char *nick);
int add_member_role(unsigned long long guild_id, unsigned long long user_id, unsigned long long role_id);
int remove_member_role(unsigned long long guild_id, unsigned long long user_id, unsigned long long role_id);
int kick_member(unsigned long long guild_id, unsigned long long user_id);
struct ban *get_bans(unsigned long long guild_id);
int ban_member(unsigned long long guild_id, unsigned long long user_id, int delete_msg_days, char *reason);
int unban_member(unsigned long long guild_id, unsigned long long user_id);
struct role *get_guild_roles(unsigned long long guild_id);
struct role *create_role(unsigned long long guild_id, struct role *role);
struct role *modify_role_pos(unsigned long long guild_id, unsigned long long role_id, int pos);
struct role *modify_role(unsigned long long guild_id, struct role *role);
int delete_role(unsigned long long guild_id, unsigned long long role_id);
unsigned int get_prune_count(unsigned long long guild_id, unsigned char days);
unsigned int begin_guild_prune(unsigned long long guild_id, unsigned char days, int compute_prune_count);
struct voice_region *get_guild_voice_regions(unsigned long long guild_id);
struct invite *get_guild_invites(unsigned long long guild_id);
struct intergration *get_guild_integrations(unsigned long long  guild_id);
int create_guild_intergation(unsigned long long guild_id, char *type, unsigned long long id);
int modify_guild_integration(unsigned long long guild_id, unsigned long long id, int exp_behavior, int exp_grace_per, unsigned char enable_emoticons);
int delete_guild_intergration(unsigned long long guild_id, unsigned long long id);
int sync_guild_integration(unsigned long long guild_id, unsigned long long id);
struct guild_embed *get_guild_embed(unsigned long long guild_id);
struct guild_embed *modify_guild_embed(unsigned long long guild_id, struct guild_embed *embed);
struct invite *get_guild_vanity_url(unsigned long long guild_id);
//void get_guild_widget_image(uint64_t guild_id);
#endif
