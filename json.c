#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <jansson.h>

#include "json.h"
#include "time.h"
#include "channel.h"
#include "emoji.h"
#include "guild.h"
#include "invite.h"
#include "user.h"
#include "voice.h"
#include "webhook.h"


/*
 * channel.h
 */

void json_to_channel(json_t *json, struct channel *channel)
{
	json_t *buf;
	
	channel->id = json_int_value(json_object_get(json, "id"));
	channel->type = json_int_value(json_object_get(json, "type"));
	channel->guild_id = json_int_value(json_object_get(json, "guild_id"));
	channel->position = json_int_value(json_object_get(json, "position"));
	channel->name = json_string_value(json_object_get(json, "name"));
	channel->topic = json_string_value(json_object_get(json, "topic"));

	if(json_is_true(json_object_get(json, "nsfw")))
		channel->nsfw = true;
	//no need to check if it false since if it isnt true the member will be false by default

	channel->last_message_id = json_int_value(json_object_get(json, "last_message_id"));
	channel->bitrate = json_int_value(json_object_get(json, "bitrate"));
	channel->user_limit = json_int_value(json_object_get(json, "user_limit"));
	channel->rate_limit = json_int_value(json_object_get(json, "rate_limit"));

	buf = json_object_get(json, "recipients");
	if(buf != NULL)
	{
		size_t index;
		size_t nmemb = json_array_size(buf);
		struct user **users = calloc(nmemb, sizeof(struct user *));
		struct user *user;
		json_t *item;

		json_array_foreach(buf, index, item)
		{
			user = malloc(sizeof(struct user));
			json_to_user(item, user);
			users[index] = user;
		}
		channel->recipients = users;
	}
	
	channel->icon = json_string_value(json_object_get(json, "icon"));
}


void json_to_message(json_t *json, struct message *message)
{
	json_t *buf;
		
	message->id = json_int_value(json_object_get(json, "id"));
	message->channel_id = json_int_value(json_object_get(json, "channel_id"));
	message->guild_id = json_int_value(json_object_get(json, "guild_id"));
	
	buf = json_object_get(json, "author");
	if(buf != NULL)
	{
		message->author = malloc(sizeof(struct user));
		json_to_user(buf, message->author);
	}
	
	buf = json_object_get(json, "member");
	if(buf != NULL)
	{
		message->member = malloc(sizeof(struct member));
		json_to_member(buf, message->member);
	}

	rv->content = json_string_value(json_object_get(json, "content"));

	if(json_is_true(json_object_get(json, "tts")))
		message->tts = true;

	if(json_is_true(json_object_get(json, "mention_everyone")))
		message->mention_everyone = true;

	/* mentions, this shit is wierd af user objects with partial member objects, ¯\_(ツ)_/¯
	 * my theory is that the array is structed as so
	 * mentions: [ { user, member}, {user, member}, ....]
	 */

	if((buf = json_object_get(json, "mentions")) != NULL)
	{
		message->mention_count = json_array_size(buf);
		struct mention **mentions = calloc(message->mention_count, sizeof(struct mention *));
		struct mention *mention;
		size_t index;
		json_t *item;
		message->mentions = mentions;

		json_array_foreach(buf, index, item)
		{
			mention = malloc(sizeof(struct mention));
			json_to_mention(item, mention)
			mentions[index] = mention;
		}
	}

	if((buf = json_object_get(json, "mention_roles")) != NULL)
	{
		message->mention_role_count = json_array_size(buf);
		unsigned long long *roles = calloc(message->mention_role_count, sizeof(unsigned long long));
		size_t index;
		json_t *item;
		message->mention_roles = roles;
		
		json_array_foreach(buf, index, item)
			roles[index] = json_int_value(item);
	}

	if((buf = json_object_get(json, "attachments")) != NULL)
	{
		struct attachment *attachment = malloc(sizeof(struct attachment));
		message->attachment = json_to_attachment(buf, attachment);
	}
	
	if((buf = json_object_get(json, "embeds")) != NULL)
	{
		message->embed_count = json_array_size(buf);
		struct embed **embeds = calloc(rv->embed_count, sizeof(struct embed *));
		struct embed *embed;
		size_t index;
		json_t *item;
		message->embeds = embeds;

		json_array_foreach(buf, index, item)
		{
			embed = malloc(sizeof(struct embed));
			json_to_embed(item, embed);
			embeds[index] = embed;
		}
	}
	
	if((buf = json_object_get(json, "reactions")) != NULL)
	{
		message->reaction_count = json_array_size(buf);
		struct reaction **reactions = calloc(rv->reaction_count, sizeof(struct reaction *));
		struct reaction *reaction;
		size_t index;
		json_t *item;
		message->reactions = reactions;

		json_array_foreach(buf, index, item)
		{
			reaction = malloc(sizeof(struct reaction));
			json_to_reaction(item, reaction);
			reactions[index] = reaction;
		}			

	}

	message->nonce = json_int_value(json_object_get(json, "nonce"));
	
	if(json_is_true(json_object_get(json, "pinned")))
		message->pinned = true;

	message->webhook_id = json_int_value(json_object_get(json, "webhook_id"));
	message->type = json_int_value(json_object(json, "type"));

	if((buf = json_object_get(json, "activity")) != NULL)
	{
		message->activity = malloc(sizeof(struct activity));
		json_to_activity(buf, message->activity);
	}
	//application
}

void json_to_activity(json_t *json struct activity *activity)
{
	activity->type = json_int_value(json_object_get(json, "type"));
	activity->party_id = json_string_value(json_object_get(json, "party_id"));
}

void json_to_application(json_ *json, struct application *application)
{
	application->id = json_int_value(json_object_get(json, "id"));
	application->cover = json_string_value(json_object_get(json, "cover_image"));
	application->description = json_string_value(json_object_get(json, "description"));
	application->icon = json_string_value(json_object_get(json, "icon"));
	application->name = json_string_value(json_object_get(json, "name"));
}

void json_to_mention(json_t *json, struct mention *mention)
{
	json_t *buf;

	mention->user = malloc(sizeof(struct user));
	json_to_user(json, user);

	if((buf = json_object json_object_get(json, "member")) != NULL)
	{
		mention->member = malloc(sizeof(struct member));
		json_to_member(buf, mention->member);
	}
}

void json_to_reaction(json_t *json, struct reaction *rv)
{
	json_t *buf;
	
	rv->count = json_number_value(json_object_get(json, "count"));

	buf = json_object_get(json, "me");
	if(json_is_true(buf))
		rv->me = true;
}


void json_to_overwrite(json_t *json, struct overwrite *rv)
{
	json_t *buf;
	rv->id = json_number_value(json_object_get(json, "id"));
	
	buf = json_object_get(json, "type")
	if(strcmp(json_string_value(buf), "member") == 0)
		rv->type = MEMBER;

	rv->allow = json_number_value(jsonwobject_get(json, "allow"));
	rv->deny = json_number_value(json_object_get(json, "deny"));
}


void json_to_embed(json_t *json, struct embed *embed)
{
	embed->title = json_string_value(json_object_get(json, "title"));
	embed->type = json_string_value(json_object_get(json, "type"));
	embed->description = json_string_value(json_object_get(json, "description"));
	embed->url = json_string_value(json_object_get(json, "url"));
	embed->color = json_number_value(json_object_get(json, "color"));
}


void json_to_attachment(json_t *json, struct attachment *attachment)
{
	attachment->id = json_number_value(json_object_get(json, "id"));
	attachment->filename = json_string_value(json_object_get(json, "filename"));
	attachment->size = json_number_value(json_object_get(json, "size"));
	attachment->proxy_url = json_string_value(json_object_get(json, "proxy_url"));
	attachment->height = json_number_value(json_object_get(json, "height"));
	attachment->width = json_number_value(json_object_get(json, "width"));
}


/*
 * emoji.h
 */


void json_to_emoji(json_t *json, struct emoji *rv)
{
	json_t *buf;
	
	rv->id = json_number_value(json_object_get(json, "id"));
	rv->name = json_string_value(json_object_get(json, "name"));

	if((buf = json_get_object(json, "roles")) != NULL)
	{
		unsigned long long *roles;
		rv->mention_role_count = json_array_size(buf);
		size_t index;
		json_t *item;
			
		roles = calloc(rv->mention_role_count, sizeof(unsigned long long));
		rv->mention_roles = roles;
		json_array_foreach(buf, index, item)
			roles[index] = json_number_value(item);

	}

	if((buf = json_object_get(json, "user")) != NULL)
	{
		emoji->user = malloc(sizeof(struct user));
		json_to_user(buf, emoji->user);
	}
		
	if(json_is_true(json_object_get(json, "require_colons")))
		rv->req_colons = true;

	if(json_is_true(json_object_get(json, "managed")))
		rv->managed = true;

	if(json_is_true(json_object_get(json, "animated")))
		rv->animated = true;
}


/*
 * guild.h
 */

void json_to_guild(json_t *json, struct guild *rv)
{
	json_t *buf;

		if(strcmp(key, "id") == 0)
			rv->id = json_number_value(val);

		if(strcmp(key, "name") == 0)
			rv->name = json_string_value(val);

		if(strcmp(key, "icon") == 0)
			rv->icon = json_string_value(val);

		if(strcmp(key, "splash") == 0)
			rv->splash = json_string_value(val);

		if(strcmp(key, "self_is_owner") == 0)
		{
			if(json_is_true(val))
				rv->self_is_owner = 1;

			else if(json_is_false(val))
				rv->self_is_owner = 0;
		}

		if(strcmp(key, "owner_id") == 0)
			rv->owner_id = json_number_value(val);

		if(strcmp(key, "permissions") == 0)
			rv->permissions = json_number_value(val);

		if(strcmp(key, "region") == 0)
			rv->region = json_string_value(val);

		if(strcmp(key, "afk_channel_id") == 0)
			rv->afk_channel_id = json_number_value(val);

		if(strcmp(key, "afk_timeout") == 0)
			rv->afk_timeout = json_number_value(val);

		if(strcmp(key, "embed_enabled") == 0)
		{
			if(json_is_true(val))
				rv->embed_enabled = 1;
			
			else if(json_is_false(val))
				rv->embed_enabled = 0;
		}

		if(strcmp(key, "embed_channel_id") == 0)
			rv->embed_channel_id = json_number_value(val);

		if(strcmp(key, "verification_level") == 0)
			rv->verification_level = json_number_value(val);

		if(strcmp(key, "notification_level") == 0)
			rv->notification_level = json_number_value(val);

		if(strcmp(key, "explicit_filter_level") == 0)
			rv->explicit_filter_level = json_number_value(val);

		if(strcmp(key, "roles") == 0)
		{	
			size_t index;
			rv->role_count = json_array_size(val);
			struct role **roles = calloc(rv->role_count, sizeof(struct role *));
			struct role *role;
			json_t *item;

						
			json_array_foreach(val, index, item)
			{
				role = malloc(sizeof(struct role));
				rv->voice_states = voice_states;
			}

		if(strcmp(key, "members") == 0)
		{
			size_t index;
			rv->member_count = json_array_size(val);
			struct member **members = calloc(rv->member_count, sizeof(struct member *));
			struct member *member;
			json_t *item;

			json_array_foreach(val, index, item)
			{
				member = malloc(sizeof(struct member));
				json_to_member(item, member);
				members[index] = member;
			}
			rv->members = members;

		}

		if(strcmp(key, "channels") == 0)
		{
			size_t index;
			rv->channel_count = json_array_size(val);
			struct channel **channels = calloc(rv->channel_count, sizeof(struct channel *));
			struct channel *channel;
			json_t *item;

			json_array_foreach(val, index, item)
			{
				channel = malloc(sizeof(struct channel));
				json_to_channel(item, channel);
				channels[index] = channel;
			}
			rv->channels = channels;
		}

		if(strcmp(key, "presences") == 0)
		{
			size_t index;
			rv->presence_count = json_array_size(val);
			struct presence **presences = calloc(rv->presence_count, sizeof(struct presence *));
			struct presence *presence;
			json_t *item;

			json_array_foreach(val, index, item)
			{
				presence = malloc(sizeof(struct presence));
				json_to_presence(item, presence);
				presences[index] = presence;
			}
			rv->presences = presences;
		}
	}
}

void json_to_guild_embed(json_t *json, struct guild_embed *rv)
{
	const char *key;
	json_t *val;

	json_object_foreach(json, key, val)
	{
		if(strcmp(key, "enabled") == 0)
		{
			if(json_is_true(val))
				rv->enabled = 1;
			
			else if(json_is_false(val))
				rv->enabled = 0;
		}

		if(strcmp(key, "channel_id") == 0)
			rv->channel_id = json_number_value(val);

	}
}


void json_to_member(json_t *json, struct member *rv)
{
	const char *key;
	json_t *val;

	json_object_foreach(json, key, val)
	{
		if(strcmp(key, "user") == 0)
			rv->user = json_to_user(val, malloc(sizeof(struct user)));

		if(strcmp(key, "nick") == 0)
			rv->nick = json_string_value(val);

		if(strcmp(key, "roles") == 0)
		{
		}

		if(strcmp(key, "joined_at") == 0)
			rv->joined_at = timefmt(json_string_value(val), malloc(sizeof(struct tm)));

		if(strcmp(key, "premium_since") == 0)
			rv->premium_since = timefmt(json_string_value(val), malloc(sizeof(struct tm)));

		if(strcmp(key, "deaf") == 0)
		{
			if(json_is_true(val))
				rv->deaf = 1;
			
			else if(json_is_false(val))
				rv->deaf = 0;
		}

		if(strcmp(key, "mute") == 0)
		{
			if(json_is_true(val))
				rv->mute = 1;

			else if(json_is_false(val))
				rv->mute = 0;
		}
	}
}


void json_to_integration(json_t *json, struct integration *rv)
{
	const char *key;
	json_t *val;

	json_object_foreach(json, key, val)
	{
		if(strcmp(key, "id") == 0)
			rv->id = json_number_value(val);

		if(strcmp(key, "name") == 0)
			rv->name = json_string_value(val);

		if(strcmp(key, "type") == 0)
			rv->type = json_string_value(val);

		if(strcmp(key, "syncing") == 0)
		{
			if(json_is_true(val))
				rv->syncing = 1;
			
			else if(json_is_false(val))
				rv->syncing = 0;
		}

		if(strcmp(key, "role_id") == 0)
			rv->role_id = json_number_value(val);

		if(strcmp(key, "expire_behavior") == 0)
			rv->expire_behavior = json_number_value(val);

		if(strcmp(key, "expire_grace_period") == 0)
			rv->expire_grace_period = json_number_value(val);

		if(strcmp(key, "user") == 0)
			rv->user = json_to_user(val, malloc(sizeof(struct user)));

		if(strcmp(key, "account") == 0)
			rv->account = json_to_integration_account(val, malloc(sizeof(struct integration_account)));

		if(strcmp(key, "synced_at") == 0)
			rv->synced_at = timefmt(json_string_value(val), malloc(sizeof(struct tm)));
	}
}

void json_to_integration_account(json_t *json, struct integration_account *rv)
{
	const char *key;
	json_t *val;

	json_object_foreach(json, key, val)
	{
		if(strcmp(key, "id") == 0)
			rv->id = json_string_value(val);

		if(strcmp(key, "name") == 0)
			rv->name = json_string_value(val);
	}
}


void json_to_ban(json_t *json, struct ban *rv)
{
	const char *key;
	json_t *val;

	json_object_foreach(json, key, val)
	{
		if(strcmp(key, "reason") == 0)
			rv->reason = json_string_value(val);

		if(strcmp(key, "user") == 0)
			rv->user = json_to_user(val, malloc(sizeof(struct user)));
	}
}

/*
 * invite.h
 */
void jsont_to_invite(json_t *json, struct invite *rv)
{
	const char *key;
	json_t *val;

	json_object_foreach(json, key, val)
	{
		if(strcmp(key, "code") == 0)
			rv->code = json_string_value(val);

		if(strcmp(key, "guild") == 0)
			rv->guild = json_to_guild(val, malloc(sizeof(struct guild)));

		if(strcmp(key, "channel") == 0)
			rv->channel = json_to_channel(val, malloc(sizeof(struct channel)));

		if(strcmp(key, "approximate_presence_count") == 0)
			rv->apprx_online = json_number_value(val);

		if(strcmp(key, "approximate_member_count") == 0)
			rv->apprx_total = json_number_value(val);

		
	}
	return rv;
}

void json_to_invite_meta(json_t *json, struct invite_meta *rv)
{
	const char *key;
	json_t *val;

	json_object_foreach(json, key, val)
	{
		if(strcmp(key, "inviter") == 0)
			rv->inviter = json_to_user(val, malloc(sizeof(struct user)));

		if(strcmp(key, "uses") == 0)
			rv->uses = json_number_value(val);

		if(strcmp(key, "max_uses") == 0)
			rv->max_uses = json_number_value(val);

		if(strcmp(key, "max_age") == 0)
			rv->max_age = json_number_value(val);

		if(strcmp(key, "temp") == 0)
		{
			if(json_is_true(val))
				rv->temp = 1;
			
			else if(json_is_false(val))
				rv->temp = 0;
		}

		if(strcmp(key, "created_at") == 0)
			rv->created_at = timefmt(json_string_value(val), malloc(sizeof(struct tm)));

		if(strcmp(key, "revoked") == 0)
		{
			if(json_is_true(val))
				rv->revoked = 1;

			else if(json_is_false(val))
				rv->revoked = 0;
		}
	}	
}
/*
 * user.h
 */
void json_to_user(json_t *json, struct user *rv)
{
	const char *key;
	json_t *val;

	json_object_foreach(json, key, val)
	{

	}
	return rv;
}

/*
 * voice.h
 * webhook.h
 */
