#ifndef channel_h
#define channel_h

#include <time.h>
#include <stdbool.h>

#include "client.h"
#include "user.h"
#include "guild.h"

enum activity_type
{
	JOIN = 1,
	SPECTATE,
	LISTEN,
	JOIN_REQUEST
};

enum overwrite_type
{
	ROLE,
	MEMBER
};

enum message_type
{
	DEFAULT,
	RECIPIENT_ADD,
	RECIPIENT_REMOVE,
	CALL,
	CHANNEL_NAME_CHANGE,
	CHANNEL_ICON_CHANGE, 
	CHANNEL_PINNED_MESSAGE,
	GUILD_MEMBER_JOIN,
	USER_PREMIUM_GUID_SUBSCRIPTION,
	USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1,
	USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2,
	USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3
};

struct channel
{
	unsigned long long id;
	unsigned char type;
	unsigned long long guild_id;
	unsigned char position;
	size_t overwrite_count;
	struct overwrite **overwrites;
	const char *name;
	const char *topic;
	bool nsfw;
	unsigned long long last_message_id;
	unsigned int bitrate;
	unsigned char user_limit;
	unsigned char rate_limit;
	size_t recipient_count;
	struct user **recipients;
	const char *icon;
	unsigned long long owner_id;
	unsigned long long application_id;
	unsigned long long parent_id;
	struct tm *last_pin_timestamp;
	
};

struct message
{
	unsigned long long id;
	unsigned long long channel_id;
	unsigned long long guild_id;
	struct user *author;
	struct member *member;
	const char *content;
	struct tm *timestamp;
	struct tm *edited_timestamp;
	bool tts;
	bool mention_everyone;
	size_t mention_count;
	struct mention **mentions;
	size_t mention_role_count;
	unsigned long long *mention_roles;
	size_t attachment_count;
	struct attachment **attachments;
	size_t embed_count;
	struct embed **embeds;
	size_t reaction_count;
	struct reaction **reactions;
	unsigned long long nonce;
	bool pinned;
	unsigned long long webhook_id;
	enum message_type type;
	struct activity *activity;
	struct application *application;

};

struct mention
{
	struct user *user;
	struct member *member;
};

struct reaction
{
	unsigned int count;
	unsigned char me;
	struct emoji *emoji;
};

struct overwrite
{
	unsigned long long id;
	enum overwrite_type type;
	unsigned char allow;
	unsigned char deny;
};

struct application
{
	unsigned long long id;
	const char *cover_image;
	const char *description;
	const char *icon;
	const char *name;
};

struct activity
{
	enum activity_type type;
	const char *party_id;
};

struct embed
{
	const char *title;
	const char *type;
	const char *description;
	const char *url;
	struct tm *timestamp;
	int color;
	struct embed_footer *footer;
	struct embed_image *image;
	struct embed_thumbnail *thumbnail;
	struct embed_video *video;
	struct embed_provider *provider;
	struct embed_author *author;
	struct embed_fields *fields;
};

struct embed_thumbnail
{
	const char *url;
	const char *proxy_url;
	unsigned int height;
	unsigned width;
};

struct embed_video
{
	const char *url;
	unsigned int height;
	unsigned int width;
};

struct embed_image
{
	const char *url;
	const char *proxy_url;
	unsigned int height;
	unsigned int width;
};

struct embed_provider
{
	const char *name;
	const char *url;
};

struct embed_author
{
	const char *name;
	const char *url;
	const char *icon_url;
	const char *proxy_icon_url;
};

struct embed_footer
{
	const char *text;
	const char *icon_url;
	const char *proxy_icon_url;
};

struct embed_fields
{
	const char *name;
	const char *value;
	bool _inline;
};

struct attachment
{
	unsigned long long id;
	const char *filename;
	unsigned long long size;
	const char *proxy_url;
	unsigned int height;
	unsigned int width;
};

struct channel *get_channel(struct client *client, unsigned long long channel_id);
int modify_channel(struct channel *channel);
int delete_channel(unsigned long long channel_id);
struct message *get_channel_messages(unsigned long long channel_id, unsigned long long around,  unsigned long long before, unsigned long long limit);
struct message *get_channel_message(unsigned long long channel_id, unsigned long long messsage_id);
int create_message(unsigned long long channel_id, char *content, unsigned long long nonce, unsigned char tts, char *file, struct embed *embed, char *payload_json);
int create_reaction(unsigned long long  channel_id, unsigned long long message_id, char *emoji);
int delete_own_rection(unsigned long long channel_id, unsigned long long message_id, char *emoji);
int delete_user_reaction(unsigned long long channel_id, unsigned long long message_id, char *emoji, unsigned long long user_id);
struct reaction *get_reactions(unsigned long long channel_id, unsigned long long message_id, char *emoji, unsigned long long before, unsigned long long after, unsigned long long limit);
int delete_all_reactions(unsigned long long channel_id, unsigned long long message_id);
int edit_message(unsigned long long channel_id, unsigned long long message_id, char *content, struct embed *embed);
int delete_message(unsigned long long channel_id, unsigned long long message_id);
int bulk_delete_messages(unsigned long long channel_id, unsigned long long *message_id, unsigned int len);
int edit_channel_perms(unsigned long long channel_id, unsigned long long overwrite_id, unsigned int allow, unsigned int deny, char *type);
int delete_channel_perms(unsigned long long channel_id, unsigned long long overwrite_id);
struct invite *get_channel_invite(unsigned long long channel_id);
int create_channel_inv(unsigned long long channel_id, unsigned long long max_age, unsigned long long max_uses, unsigned int temp, unsigned int unique);
int trigger_typing(unsigned long long channel_id);
struct message *get_pinned_messages(unsigned long long channel_id);
int pin_message(unsigned long long channel_id, unsigned long long  message_id);
int delete_pinned_message(unsigned long long channel_id, unsigned long long message_id);
int group_add_recip(unsigned long long channel_id, unsigned long user_id, char *access_token, char *nick);
int group_remove_recip(unsigned long long channel_id, unsigned long long user_id);
#endif
