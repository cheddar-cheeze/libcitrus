#ifndef CHANNEL_H
#define CHANNEL_H
#include <stdint.h>
#include "util.h"

typedef struct
{
	uint64_t id;
	int type;
	uint64_t guild_id;
	int position;
	//permission_overwrites
	char *name;
	char *topic;
	int nsfw;
	uint64_t last_message_id;
	uint16_t bitrate;
	int user_limit;
	uint8_t rate_limit;
	user *recipients;
	char *icon;
	uint64_t icon;
	//application_id
	//parent_id
	//last_pin_timestamp  REALLY FUCK 
	//ISO8601 TIMESTAMPS CANT THEY JUST 
	//USE UNIX TIMESTAMPS
} channel_t;

typedef struct
{
	uint64_t id;
	uint64_t channel_id;
	uint64_t guild_id;
	user author;
	member member;
	char *content;
	//shitty timestamp >:(
	//another shitty timestamp fuck
	int tts;
	int mention_everyone;
	//mentions
	uint64_t mention_roles;
	//attachments
	//embeds
	//reactions
	uint64_t nonce;
	int pinned;
	uint64_t webhook_id;
	int type;
	//activity
	//application
} message_t;

typedef struct
{
	uint16_t count;
	int me;
	//emoji
} reaction_t;

typedef struct
{
	uint64_t id;
	char *type;
	int allow;
	int deny;
} overwrite_t;

typedef struct
{
	char *title;
	char *type;
	char *description;
	char *url;
	//FUCK NON UNIX TIMESTAMPS
	uint8_t color;
	//more types included
} embed_t;

typedef struct
{
	uint64_t id;
	char *filename;
	uint64_t size;
	char *proxy_url;
	uint16_t height;
	uint16_t width;
} attachment_t;


int free_channel(channel_t *channel);

int free_message(message_t *message);

channel_t *get_channel(uint64_t channel_id);

int modify_channel(channel_t *channel);

int delete_channel(uint64_t channel_id);

vec_t *get_channel_messages(uint64_t channel_id, uint64_t around, 
		uint64_t before, uint64_t limit);

message_t *get_channel_message(uint64_t channel_id, uint64_t messsage_id);

int create_message(uint64_t channel_id, char *content, uint64_t nonce, int tts,
		char *file, embed_t *embed, char *payload_json);

int create_reaction(uint64_t channel_id, uint64_t message_id, char *emoji);

int delete_own_rection(uint64_t channel_id, uint64_t message_id, char *emoji);

int delete_user_reaction(uint64_t channel_id, uint64_t message_id, char *emoji, uint64_t user_id);

vec_t *get_reactions(uint64_t channel_id, uint64_t message_id, char *emoji, uint64_t before,
		uint64_t after, uint64_t limit);

int delete_all_reactions(uint64_t channel_id, uint64_t message_id);

int edit_message(uint64_t channel_id, uint64_t message_id, char *content, embed_t *embed);

int delete_message(uint64_t channel_id, uint64_t message_id);

int bulk_delete_messages(uint64_t channel_id, vec_t *message_id);

int edit_channel_perms(uint64_t channel_id, uint64_t overwrite_id, int allow, int deny, char *type);

int delete_channel_perms(uint64_t channel_id, uint64_t overwrite_id);

vec_t *get_channel_invite(uint64_t channel_id);

int create_channel_inv(uint64_t channel_id, uint16_t max_age, uint16_t max_uses, int temp, int unique);

int trigger_typing(uint64_t channel_id);

vec_t *get_pinned messages(uint64_t channel_id);

int pin_message(uint64_t channel_id, uint64_t message_id);

int delete_pinned_message(uint64_t channel_id, uint64_t message_id);

int group_add_recip(uint64_t channel_id, uint64_t user_id, char *access_token, char *nick);

int group_remove_recip(uint64_t channel_id, uint64_t user_id);

#endif
