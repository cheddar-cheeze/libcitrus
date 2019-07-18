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

struct channel *json_to_channel(json_t *json, struct channel *rv)
{
	const char *key;
	json_t *val;
	
	json_object_foreach(json, key, val)
	{
		if(strcmp(key, "id") == 0)
			rv->id = json_number_value(val);

		if(strcmp(key, "type") == 0)
			rv->type = json_number_value(val);

		if(strcmp(key, "guild_id") == 0)
			rv->guild_id = json_number_value(val);

		if(strcmp(key, "position") == 0)
			rv->position = json_number_value(val);

		if(strcmp(key, "name") == 0)
			rv->name = json_string_value(val);
		
		if(strcmp(key, "topic") == 0)
			rv->topic = json_string_value(val);

		if(strcmp(key, "nsfw") == 0)
		{
			if(json_is_true(val))
				rv->nsfw = true;

			if(json_is_false(val))
				rv->nsfw = false;
		}

		if(strcmp(key, "last_message_id") == 0)
			rv->last_message_id = json_number_value(val);

		if(strcmp(key, "bitrate") == 0)
			rv->bitrate = json_number_value(val);

		if(strcmp(key, "user_limit") == 0)
			rv->user_limit = json_number_value(val);

		if(strcmp(key, "rate_limit") == 0)
			rv->rate_limit = json_number_value(val);

		if(strcmp(key, "recipients") == 0)
		{
			/*
			 * creates a linked list of users, for the recipients member
			 * REVISIONS MAY OCCUR
			 */

			size_t index;
			size_t nmemb = json_array_size(val);
			struct user **users = calloc(nmemb, sizeof(struct user *));
			struct user *user;
			json_t *item;

			json_array_foreach(val, index, item)
			{
				user = malloc(sizeof(struct user));
				json_to_user(item, user);
				users[index] = user;
			}
			rv->recipients = users;
		}


		if(strcmp(key, "icon") == 0)
			rv->icon = json_string_value(val);
	}
	return rv;
}


struct message *json_to_message(json_t *json, struct message *rv)
{
	const char *key;
	json_t *val;

	json_object_foreach(json, key, val)
	{
		if(strcmp(key, "id") == 0)
			rv->id = json_number_value(val);

		if(strcmp(key, "channel_id") == 0)
			rv->channel_id = json_number_value(val);

		if(strcmp(key, "guild_id") == 0)
			rv->guild_id = json_number_value(val);

		if(strcmp(key, "author") == 0)
		{
			struct user *user;
			user = malloc(sizeof(struct user));
			rv->author = json_to_user(val, user);
		}

		if(strcmp(key, "member") == 0)
		{
			struct member *member;
			member = malloc(sizeof(struct member));
			rv->member = json_to_member(val, member);
		}

		if(strcmp(key, "content") == 0)
			rv->content = json_string_value(val);

		if(strcmp(key, "tts") == 0)
		{
			if(json_is_true(val))
				rv->tts = true;

			if(json_is_false(val))
				rv->tts = false;
		}

		if(strcmp(key, "mention_everyone") == 0)
			rv->mention_everyone = 1;

		if(strcmp(key, "mention_roles") == 0)
		{
			unsigned long long *roles;
			size_t nmemb = json_array_size(val);
			size_t index;
			json_t *item;
			
			roles = calloc(nmemb, sizeof(unsigned long long));
			rv->mention_roles = roles;
			json_array_foreach(val, index, item)
				roles[index] = json_number_value(item);
		}
	}
	return rv;
}


struct reaction *json_to_reaction(json_t *json, struct reaction *rv)
{
	const char *key;
	json_t *val;

	json_object_foreach(json, key, val)
	{
		if(strcmp(key, "count") == 0)
			rv->count = json_number_value(val);

		if(strcmp(key, "me") == 0)
		{
			if(json_is_true(val))
				rv->me = 1;
			else if(json_is_false(val))
				rv->me = 0;
		}
	}
	return rv;
}


struct overwrite *json_to_overwrite(json_t *json, struct overwrite *rv)
{
	const char *key;
	json_t *val;

	json_object_foreach(json, key, val)
	{
		if(strcmp(key, "id") == 0)
			rv->id = json_number_value(val);

		if(strcmp(key, "type") == 0)
		{
			if(strcmp(json_string_value(val), "role") == 0)
				rv->type = ROLE;

			if(strcmp(json_string_value(val), "mention") == 0)
				rv->type = MEMBER;
		}

		if(strcmp(key, "allow") == 0)
			rv->allow = json_number_value(val);

		if(strcmp(key, "deny") == 0)
			rv->deny = json_number_value(val);

	}
	return rv;
}


struct embed *json_to_embed(json_t *json, struct embed *rv)
{
	const char *key;
	json_t *val;

	json_object_foreach(json, key, val)
	{
		if(strcmp(key, "title") == 0)
			rv->title = json_string_value(val);

		if(strcmp(key, "type") == 0)
			rv->type = json_string_value(val);

		if(strcmp(key, "description") == 0)
			rv->description = json_string_value(val);

		if(strcmp(key, "url") == 0)
			rv->url = json_string_value(val);

		if(strcmp(key, "color") == 0)
			rv->color = json_number_value(val);
	}
	return rv;
}


struct attachment *json_to_attachment(json_t *json, struct attachment *rv)
{

	const char *key;
	json_t *val;

	json_object_foreach(json, key, val)
	{
		if(strcmp(key, "id") == 0)
			rv->id = json_number_value(val);

		if(strcmp(key, "filename") == 0)
			rv->filename = json_string_value(val);

		if(strcmp(key, "size") == 0)
			rv->size = json_number_value(val);

		if(strcmp(key, "proxy_url") == 0)
			rv->proxy_url = json_string_value(val);

		if(strcmp(key, "height") == 0)
			rv->height = json_number_value(val);

		if(strcmp(key, "width") == 0)
			rv->width = json_number_value(val);
	}
	return rv;
}


/*
 * emoji.h
 */


struct emoji *json_to_emoji(json_t *json, struct emoji *rv)
{
	const char *key;
	json_t *val;

	json_object_foreach(json, key, val)
	{
		if(strcmp(key, "id") == 0)
			rv->id = json_number_value(val);

		if(strcmp(key, "name") == 0)
			rv->name = json_string_value(val);

		if(strcmp(key, "roles") == 0)
		{
		}

		if(strcmp(key, "user") == 0)
		{
			struct user *user = malloc(sizeof(struct user));
			rv->user = json_to_user(val, user);
		}

		if(strcmp(key, "req_colons") == 0)
		{
			if(json_is_true(val))
				rv->req_colons = 1;

			if(json_is_false(val))
				rv->req_colons = 0;
		}

		if(strcmp(key, "managed") == 0)
		{
			if(json_is_true(val))
				rv->managed = 1;

			if(json_is_false(val))
				rv->managed = 0;
		}

		if(strcmp(key, "animated"))
		{
			if(json_is_true(val))
				rv->animated = 1;

			if(json_is_false(val))
				rv->animated = 0;
		}
	}
	return rv;
}


/*
 * guild.h
 */

struct guild *json_to_guild(json_t *json, struct guild *rv)
{
	const char *key;
	json_t *val;

	json_object_foreach(json, key, val)
	{
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
	return rv;
}

struct guild_embed *json_to_guild_embed(json_t *json, struct guild_embed *rv)
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
	return rv;
}


struct member *json_to_member(json_t *json, struct member *rv)
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
	return rv;
}


struct integration *json_to_integration(json_t *json, struct integration *rv)
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
	return rv;
}

struct integration_account *json_to_integration_account(json_t *json, struct integration_account *rv)
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
	return rv;
}


struct ban *json_to_ban(json_t *json, struct ban *rv)
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
	return rv;
}

/*
 * invite.h
 */
struct invite *jsont_to_invite(json_t *json, struct invite *rv)
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

struct invite_meta *json_to_invite_meta(json_t *json, struct invite_meta *rv)
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
struct user *json_to_user(json_t *json, struct user *rv)
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
