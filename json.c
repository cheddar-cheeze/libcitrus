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

struct channel *json_to_channel(const char *json)
{
	const char *key;
	json_t *val;
	struct channel *rv;
	
	rv = malloc(sizeof(struct channel));

	json_object_foreach(obj, key, val)
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
			//iterate over json array and create user objects using linked lists
			rv->recipients = json_array_value(val);

		if(strncmp(key, "icon") == 0)
			rv->icon = json_string_value(val);
	}
	return rv;
}


struct message *json_to_message(const char *json)
{
	const char *key;
	json_t *val;
	struct message *rv;

	rv = malloc(sizeof(struct message));

	json_object_foreach(obj, key, val)
	{
		if(strcmp(key, "id") == 0)
			rv->id = json_number_value(val);

		if(strcmp(key, "channel_id") == 0)
			rv->channel_id = json_number_value(val);

		if(strcmp(key, "guild_id") == 0)
			rv->guild_id = json_number_value(val);

		if(strcmp(key, "author") == 0)
		{
			//? tf
			rv->author = json_to_user();
		}

		if(strncmp(key, "member") == 0)
			//another json object that is wierd to parse
			rv->member = NULL;

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

		/*
		 * if(strcmp(key, "mention_roles") == 0)
		 * this is supposed to be able to handle mutliple role id
		 */
	}
	return rv;
}


struct reaction *json_to_reaction(const char *json)
{
}


struct overwrite *json_to_overwrite(const char *json)
{
}


struct embed *json_to_embed(const char *json)
{
}


struct attachment *json_to_attachment(const char *json)
{
}


/*
 * emoji.h
 */


struct emoji *json_to_emoji(const char *json)
{
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
