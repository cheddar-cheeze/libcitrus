#pragma once
#include "client.h"

struct channel
{
	unsigned long long id;
	unsigned char type;
	unsigned long long guild_id;
	unsigned char position;
	//permission_overwrites
	char *name;
	char *topic;
	unsigned char nsfw;
	unsigned long long last_message_id;
	unsigned int bitrate;
	unsigned char user_limit;
	unsigned char rate_limit;
	struct user *recipients;
	char *icon;
	//application_id
	//parent_id
	//last_pin_timestamp  REALLY FUCK 
	//ISO8601 TIMESTAMPS CANT THEY JUST 
	//USE UNIX TIMESTAMPS
};

struct message
{
	unsigned long long id;
	unsigned long long channel_id;
	unsigned long long guild_id;
	struct user *author;
	struct member *member;
	char *content;
	//shitty timestamp >:(
	//another shitty timestamp fuck
	unsigned char tts;
	unsigned char mention_everyone;
	//mentions
	unsigned long long mention_roles;
	//attachments
	//embeds
	//reactions
	unsigned long long nonce;
	unsigned char pinned;
	unsigned long long webhook_id;
	unsigned char type;
	//activity
	//application
};

struct reaction
{
	unsigned int count;
	unsigned char me;
	//emoji
};

struct overwrite
{
	unsigned long long id;
	char *type;
	unsigned char allow;
	unsigned char deny;
};

struct embed
{
	char *title;
	char *type;
	char *description;
	char *url;
	//FUCK NON UNIX TIMESTAMPS
	unsigned char color;
	//more types included
};

struct attachment
{
	unsigned long long id;
	char *filename;
	unsigned long long size;
	char *proxy_url;
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
