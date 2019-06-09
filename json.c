#include <stdlib.h>
#include <string.h>
#include <jansson.h>

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
				rv->nsfw = 1;

			if(json_if_false(val))
				rv->nsfw = 0
		}

		if(strncmp(key, "last_message_id") == 0)
			rv->last_message_id = json_number_value(val);

		if(strncmp(key, "bitrate") == 0)
			rv->bitrate = json_number_value(val);

		if(strncmp(key, "user_limit") == 0)
			rv->user_limit = json_number_value(val);

		if(strncmp(key, "rate_limit") == 0)
			rv->rate_limit = json_number_value(val);

		if(strncmp(key, "recipients") == 0)
		{
			/*
			 * creates a linked list of users, for the recipients member
			 */

			struct user *user;
			size_t index;
			json_t *item;

			user = malloc(sizeof(struct user));
			rv->recipients = user;
			json_array_foreach(val, index, item)
			{
				json_to_user(item, user);
				user->next = malloc(sizeof(struct user));
				user = user->next
			}
		}


		if(strncmp(key, "icon") == 0)
			rv->icon = json_string_value(val);
	}
	return rv;
}


struct message *json_to_message(json_t *json, struct channel *rv)
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
			user = malloc(struct user);
			rv->author = json_to_user(val, user);
		}

		if(strncmp(key, "member") == 0)
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
				rv->tts = 1;

			if(json_is_false(val))
				rv->tts = 0;
		}

		if(strcmp(key, "mention_everyone") == 0)
			rv->mention_everyone = 1;

		if(strcmp(key, "mention_roles") == 0)
		{
			/*
			 * nmemb will allways be one more than the actual 
			 * count of the roles to idenfidify the end of the array
			 * It is a null as well
			 */

			unsigned long long *roles;
			size_t nmemb;
			size_t index
			json_t *item;

			nmemb = json_array_size(val) + 1;
			
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
			else(json_is_false(val))
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

		if(strcmp(key, "type" == 0))
		{
			if(strcmp(json_string_value(val), "role") == 0)
				rv->type = ROLE;

			if(strcmp(json_string_value(val, "mention")) == 0)
				rv->type = MENTION;
		}

		if(strcmp(key, "allowed") == 0)
			rv->allowed = json_number_value(val);

		if(strcmp(key, "denied") == 0)
			rv->allowed = json_number_value(val);

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
			rv->user = json_to_user(val);

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


struct guild *json_to_guild(const char *json)
{

}


struct guild_embed *json_to_guild_embed(const char *json)
{
}


struct member *json_to_member(const char *json)
{
}


struct integration *json_to_integration(const char *json)
{
}

struct integration_account *json_to_integration_account(const char *json)
{
}


struct ban *json_to_ban(const char *json)
{
}


/*
 * invite.h
 */

struct invite *jsont_to_invite(const char *json)
{
}


struct invite_meta *json_to_invite_meta(const char *json)
{
}

/*
 * user.h
 */

struct user *json_to_user(const char *json)
{
}

/*
 * voice.h
 * webhook.h
 */
