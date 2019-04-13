struct guild
{
	unsigned long long id;
	char *name;
	char *icon;
	char *splash;
	unsigned char self_is_owner;
	unsigned long long owner_id;
	int permissions;
	char *region;
	unsigned long long afk_channel_id;
	unsigned int afk_timeout;
	unsigned char  embed_enabled;
	unsigned long long embed_channel_id;
	unsigned char verification_level;
	unsigned char notification_level;
	unsigned char explicit_filter_level;
	struct role *roles;
	struct emoji *emojis;
	struct feature *features;
	unsigned char mfa_level;
	unsigned long long application_id;
	unsigned char widget_enabled;
	unsigned long long system_channel_id;
	//joined at, shitty timestamp
	unsigned char large;
	unsigned char unavailible;
	unsigned int member_count;
	struct voice_state *voice_states;
	struct member *members;
	struct channel *channels;
	struct presence *presences;
};

enum notification level
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
	NONE,
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
	char *nick;
	struct *roles;
	//shitty timestamp;
	unsigned char deaf;
	unsigned char mute;
};

struct integration
{
	unsigned long long id;
	char *name;
	char *type;
	unsigned char syncing;
	unsigned long long role_id;
	unsigned int expire_behavior;
	unsigned int expire_grace_period;
	struct user *user;
	//account;
	//shitty iso timestamp;
};

struct integration_account
{	
	char *id;
	char *name;
};

struct ban
{
	char *reason;
	struct user *user;
};

struct guild *create_guild(struct guild *guild);
struct guild *get_guild(unsigned long long guild_id);
struct guild *modify_guild(unsigned long long *guild);
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
