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
	
	channel->id = json_integer_value(json_object_get(json, "id"));
	channel->type = json_integer_value(json_object_get(json, "type"));
	channel->guild_id = json_integer_value(json_object_get(json, "guild_id"));
	channel->position = json_integer_value(json_object_get(json, "position"));
	channel->name = json_string_value(json_object_get(json, "name"));
	channel->topic = json_string_value(json_object_get(json, "topic"));

	if(json_is_true(json_object_get(json, "nsfw")))
		channel->nsfw = true;
	//no need to check if it false since if it isnt true the member will be false by default

	channel->last_message_id = json_integer_value(json_object_get(json, "last_message_id"));
	channel->bitrate = json_integer_value(json_object_get(json, "bitrate"));
	channel->user_limit = json_integer_value(json_object_get(json, "user_limit"));
	channel->rate_limit = json_integer_value(json_object_get(json, "rate_limit"));

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
		
	message->id = json_integer_value(json_object_get(json, "id"));
	message->channel_id = json_integer_value(json_object_get(json, "channel_id"));
	message->guild_id = json_integer_value(json_object_get(json, "guild_id"));
	
	//we always check to see if the object exists before allocating memory for it so that we don't waste un-needed memory
	if((buf = json_object_get(json, "author")) != NULL)
	{
		message->author = malloc(sizeof(struct user));
		json_to_user(buf, message->author);
	}
	
	if((buf = json_object_get(json, "member")) != NULL)
	{
		message->member = malloc(sizeof(struct member));
		json_to_member(buf, message->member);
	}

	message->content = json_string_value(json_object_get(json, "content"));

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
			json_to_mention(item, mention);
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
			roles[index] = json_integer_value(item);
	}

	if((buf = json_object_get(json, "attachments")) != NULL)
	{
		message->attachment_count = json_array_size(buf);
                struct attachment **attachments = calloc(message->attachment_count, sizeof(struct attachment *));
                struct attachment *attachment;
                size_t index;
                json_t *item;
                message->attachments = attachments;

                json_array_foreach(buf, index, item)
                {
                        attachment = malloc(sizeof(struct attachment));
                        json_to_attachment(item, attachment);
                        attachments[index] = attachment;
                }
	}
	
	if((buf = json_object_get(json, "embeds")) != NULL)
	{
		message->embed_count = json_array_size(buf);
		struct embed **embeds = calloc(message->embed_count, sizeof(struct embed *));
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
		struct reaction **reactions = calloc(message->reaction_count, sizeof(struct reaction *));
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

	message->nonce = json_integer_value(json_object_get(json, "nonce"));
	
	if(json_is_true(json_object_get(json, "pinned")))
		message->pinned = true;

	message->webhook_id = json_integer_value(json_object_get(json, "webhook_id"));
	message->type = json_integer_value(json_object_get(json, "type"));

	if((buf = json_object_get(json, "activity")) != NULL)
	{
		message->activity = malloc(sizeof(struct activity));
		json_to_activity(buf, message->activity);
	}
	
	if((buf = json_object_get(json, "application")) != NULL)
	{
		message->application = malloc(sizeof(struct application));
		json_to_application(buf, message->application);
	}
}

void json_to_activity(json_t *json, struct activity *activity)
{
	activity->type = json_integer_value(json_object_get(json, "type"));
	activity->party_id = json_string_value(json_object_get(json, "party_id"));
}

void json_to_application(json_t *json, struct application *application)
{
	application->id = json_integer_value(json_object_get(json, "id"));
	application->cover_image = json_string_value(json_object_get(json, "cover_image"));
	application->description = json_string_value(json_object_get(json, "description"));
	application->icon = json_string_value(json_object_get(json, "icon"));
	application->name = json_string_value(json_object_get(json, "name"));
}

void json_to_mention(json_t *json, struct mention *mention)
{
	json_t *buf;
	
	if((buf = json_object_get(json, "user")))
	{
		mention->user = malloc(sizeof(struct user));
		json_to_user(buf, mention->user);
	}

	if((buf = json_object_get(json, "member")) != NULL)
	{
		mention->member = malloc(sizeof(struct member));
		json_to_member(buf, mention->member);
	}
}

void json_to_reaction(json_t *json, struct reaction *reaction)
{
	reaction->count = json_integer_value(json_object_get(json, "count"));

	if(json_is_true(json_object_get(json, "me")))
		reaction->me = true;
}


void json_to_overwrite(json_t *json, struct overwrite *overwrite)
{
	overwrite->id = json_integer_value(json_object_get(json, "id"));
	
	if(strcmp(json_string_value(json_object_get(json, "type")), "member") == 0)
		overwrite->type = MEMBER;

	overwrite->allow = json_integer_value(json_object_get(json, "allow"));
	overwrite->deny = json_integer_value(json_object_get(json, "deny"));
}


void json_to_embed(json_t *json, struct embed *embed)
{
	embed->title = json_string_value(json_object_get(json, "title"));
	embed->type = json_string_value(json_object_get(json, "type"));
	embed->description = json_string_value(json_object_get(json, "description"));
	embed->url = json_string_value(json_object_get(json, "url"));
	embed->color = json_integer_value(json_object_get(json, "color"));
}


void json_to_attachment(json_t *json, struct attachment *attachment)
{
	attachment->id = json_integer_value(json_object_get(json, "id"));
	attachment->filename = json_string_value(json_object_get(json, "filename"));
	attachment->size = json_integer_value(json_object_get(json, "size"));
	attachment->proxy_url = json_string_value(json_object_get(json, "proxy_url"));
	attachment->height = json_integer_value(json_object_get(json, "height"));
	attachment->width = json_integer_value(json_object_get(json, "width"));
}


/*
 * emoji.h
 */


void json_to_emoji(json_t *json, struct emoji *emoji)
{
	json_t *buf;
	
	emoji->id = json_integer_value(json_object_get(json, "id"));
	emoji->name = json_string_value(json_object_get(json, "name"));

	if((buf = json_object_get(json, "roles")) != NULL)
	{
		unsigned long long *roles;
		emoji->role_count = json_array_size(buf);
		size_t index;
		json_t *item;
			
		roles = calloc(emoji->role_count, sizeof(unsigned long long));
		emoji->roles = roles;
		json_array_foreach(buf, index, item)
			roles[index] = json_integer_value(item);

	}

	if((buf = json_object_get(json, "user")) != NULL)
	{
		emoji->user = malloc(sizeof(struct user));
		json_to_user(buf, emoji->user);
	}
		
	if(json_is_true(json_object_get(json, "require_colons")))
		emoji->req_colons = true;

	if(json_is_true(json_object_get(json, "managed")))
		emoji->managed = true;

	if(json_is_true(json_object_get(json, "animated")))
		emoji->animated = true;
}


/*
 * guild.h
 */

void json_to_guild(json_t *json, struct guild *guild)
{
	json_t *buf;

	guild->id = json_integer_value(json_object_get(json, "id"));
	guild->name = json_string_value(json_object_get(json, "name"));
	guild->icon = json_string_value(json_object_get(json, "icon"));
	guild->splash = json_string_value(json_object_get(json, "splash"));

	if(json_is_true(json_object_get(json, "owner")))
		guild->self_is_owner = true;


	guild->owner_id = json_integer_value(json_object_get(json, "owner_id"));
	guild->permissions = json_integer_value(json_object_get(json, "permissions"));
	guild->region = json_string_value(json_object_get(json, "region"));
	guild->afk_channel_id = json_integer_value(json_object_get(json, "afk_chanel_id"));
	guild->afk_timeout = json_integer_value(json_object_get(json, "afk_timeout"));

	if(json_is_true(json_object_get(json, "embed_enabled")))
		guild->embed_enabled = true;
			
	guild->embed_channel_id = json_integer_value(json_object_get(json, "embed_channel_id"));
	guild->verification_level = json_integer_value(json_object_get(json, "verification_level"));
	guild->notification_level = json_integer_value(json_object_get(json, "notification_level"));
	guild->explicit_filter_level = json_integer_value(json_object_get(json, "explicit_filter_level"));

	if((buf = json_object_get(json, "roles")) != NULL)
	{	
		size_t index;
		guild->voice_state_count = json_array_size(buf);
		struct voice_state **voice_states = calloc(guild->voice_state_count, sizeof(struct voice_state *));
		struct voice_state *voice_state;
		json_t *item;

						
		json_array_foreach(buf, index, item)
		{
			voice_state = malloc(sizeof(struct voice_state));
			guild->voice_states = voice_states;
		}
	}

	if((buf = json_object_get(json, "members")) != NULL)
	{
		size_t index;
		guild->member_count = json_array_size(buf);
		struct member **members = calloc(guild->member_count, sizeof(struct member *));
		struct member *member;
		json_t *item;

		json_array_foreach(buf, index, item)
		{
			member = malloc(sizeof(struct member));
			json_to_member(item, member);
			members[index] = member;
		}
		guild->members = members;

	}

	if((buf = json_object_get(json, "channels")) != NULL)
	{
		size_t index;
		guild->channel_count = json_array_size(buf);
		struct channel **channels = calloc(guild->channel_count, sizeof(struct channel *));
		struct channel *channel;
		json_t *item;

		json_array_foreach(buf, index, item)
		{
			channel = malloc(sizeof(struct channel));
			json_to_channel(item, channel);
			channels[index] = channel;
		}
		guild->channels = channels;
	}

	if((buf = json_object_get(json, "presences")) != NULL)
	{
		size_t index;
		guild->presence_count = json_array_size(buf);
		struct presence **presences = calloc(guild->presence_count, sizeof(struct presence *));
		struct presence *presence;
		json_t *item;

		json_array_foreach(buf, index, item)
		{
			presence = malloc(sizeof(struct presence));
			json_to_presence(item, presence);
			presences[index] = presence;
		}
		guild->presences = presences;
	}
}

void json_to_presence(json_t *json, struct presence *presence)
{
	json_t *buf;

	if((buf = json_object_get(json, "user")) != NULL)
	{
		presence->user = malloc(sizeof(struct user));
		json_to_user(buf, presence->user);
	}

	if((buf = json_object_get(json, "roles")) != NULL)
	{
		presence->role_count = json_array_size(buf);
		unsigned long long *roles = calloc(presence->role_count, sizeof(unsigned long long));
		size_t index;
		json_t *item;
		presence->roles = roles;
		
		json_array_foreach(buf, index, item)
			roles[index] = json_integer_value(item);
	}

	if((buf = json_object_get(json, "game")) != NULL)
	{
		presence->game = malloc(sizeof(struct activity));
		json_to_activity(buf, presence->game);
	}

	presence->guild_id = json_integer_value(json_object_get(json, "guild_id"));
	presence->status = json_string_value(json_object_get(json, "status"));

	if((buf = json_object_get(json, "activites")) != NULL)
	{
		size_t index;
		presence->activity_count = json_array_size(buf);
		struct activity **activities = calloc(presence->activity_count, sizeof(struct activity *));
		struct activity *activity;
		json_t *item;
		presence->activities = activities;

		json_array_foreach(buf, index, item)
		{
			activity = malloc(sizeof(struct activity));
			json_to_activity(item, activity);
			activities[index] = activity;
		}

	}
}

void json_to_guild_embed(json_t *json, struct guild_embed *guild_embed)
{

	if(json_is_true(json_object_get(json, "enabled")))
		guild_embed->enabled = true;
	
	guild_embed->channel_id = json_integer_value(json_object_get(json, "channel_id"));
}


void json_to_member(json_t *json, struct member *member)
{
	json_t *buf;
	
	if((buf = json_object_get(json, "user")) != NULL)
	{
		member->user = malloc(sizeof(struct user));
		json_to_user(buf, member->user);
	}

	if((buf = json_object_get(json, "roles")) != NULL)
	{
		member->role_count = json_array_size(buf);
		unsigned long long *roles = calloc(member->role_count, sizeof(unsigned long long));
		size_t index;
		json_t *item;
		member->roles = roles;
		
		json_array_foreach(buf, index, item)
			roles[index] = json_integer_value(item);
	}
	
	if((buf = json_object_get(json, "joined_at")) != NULL)
	{
		member->joined_at = malloc(sizeof(struct tm));
		timefmt(json_string_value(buf), member->joined_at);
	}
	
	if((buf = json_object_get(json, "premium_since")) != NULL)
	{
		member->premium_since = malloc(sizeof(struct tm));
		timefmt(json_string_value(buf), member->premium_since);
	}

	if(json_is_true(json_object_get(json, "deaf")))
		member->deaf = true;
			
	if(json_is_true(json_object_get(json, "mute")))
		member->mute = true;

}


void json_to_integration(json_t *json, struct integration *integration)
{
	json_t *buf;

	integration->id = json_integer_value(json_object_get(json, "id"));
	integration->name = json_string_value(json_object_get(json, "name"));
	integration->type = json_string_value(json_object_get(json, "type"));

	if(json_is_true(json_object_get(json, "syncing")))
		integration->syncing = true;
			
	integration->role_id = json_integer_value(json_object_get(json, "role_id"));
	integration->expire_behavior = json_integer_value(json_object_get(json, "expire_behavior"));
	integration->expire_grace_period = json_integer_value(json_object_get(json,"expire_grace_period"));

	if((buf = json_object_get(json, "user")) != NULL)
	{
		integration->user = malloc(sizeof(struct user));
		json_to_user(buf, integration->user);
	}

	if((buf = json_object_get(json, "account")) != NULL)
	{

		integration->account = malloc(sizeof(struct integration_account));
		json_to_integration_account(buf, integration->account);
	}
	
	if((buf = json_object_get(json, "synced_at")) != NULL)
	{
		integration->synced_at = malloc(sizeof(struct tm));
		timefmt(json_string_value(buf), integration->synced_at);
	}
}

void json_to_integration_account(json_t *json, struct integration_account *integration_account)
{
	integration_account->id = json_string_value(json_object_get(json, "id"));
	integration_account->name = json_string_value(json_object_get(json, "name"));
}


void json_to_ban(json_t *json, struct ban *ban)
{
	json_t *buf;

	ban->reason = json_string_value(json_object_get(json, "reason"));

	if((buf = json_object_get(json, "user")) != NULL)
	{
		ban->user = malloc(sizeof(struct user));
		json_to_user(buf, ban->user);
	}
}

/*
 * invite.h
 */
void jsont_to_invite(json_t *json, struct invite *invite)
{
	json_t *buf;

	invite->code = json_string_value(json_object_get(json, "code"));

	if((buf = json_object_get(json, "guild")) != NULL)
	{
		invite->guild = malloc(sizeof(struct guild));
		json_to_guild(buf, invite->guild);
	}
	
	if((buf = json_object_get(json, "channel")) != NULL)
	{
		invite->channel = malloc(sizeof(struct channel));
		json_to_channel(buf, invite->channel);
	}

	invite->apprx_online = json_integer_value(json_object_get(json, "approximate_presence_count"));
	invite->apprx_total = json_integer_value(json_object_get(json, "approximate_member_count"));		
}

void json_to_invite_meta(json_t *json, struct invite_meta *invite_meta)
{
	json_t *buf;

	if((buf = json_object_get(json, "inviter")) != NULL)
	{
		invite_meta->inviter = malloc(sizeof(struct user));
		json_to_user(buf, invite_meta->inviter);
	}
	
	invite_meta->uses = json_number_value(json_object_get(json, "uses"));
	invite_meta->max_uses = json_number_value(json_object_get(json, "max_uses"));
	invite_meta->max_age = json_number_value(json_object_get(json, "max_age"));

	if(json_is_true(json_object_get(json, "temp")))
		invite_meta->temp = true;
	
	if((buf = json_object_get(json, "created_at")) != NULL)
	{
		invite_meta->created_at = malloc(sizeof(struct tm));
		timefmt(json_string_value(buf), invite_meta->created_at);
	}
	
	if(json_is_true(json_object_get(json, "revoked")))			
		invite_meta->revoked = true;

}
/*
 * user.h
 */
void json_to_user(json_t *json, struct user *user)
{
	user->id = json_integer_value(json_object_get(json, "id"));
	user->username = json_string_value(json_object_get(json, "username"));
	user->discriminator = json_string_value(json_object_get(json, "discriminator"));
	user->avatar = json_string_value(json_object_get(json, "avatar"));

	if(json_is_true(json_object_get(json, "bot")))
		user->bot = true;

	if(json_is_true(json_object_get(json, "mfa_enabled")))
		user->mfa_enabled = true;
	
	user->locale = json_string_value(json_object_get(json, "locale"));
	
	if(json_is_true(json_object_get(json, "verified")))
		user->verified = true;
	
	user->email = json_string_value(json_object_get(json, "email"));
	user->flags = json_integer_value(json_object_get(json, "flags"));
	
	if(json_is_true(json_object_get(json, "premium_type")))
		user->premium = true;
}

/*
 * voice.h
 */
void json_to_voice_state(json_t *json, struct voice_state *voice_state)
{
	json_t *buf;

	voice_state->guild_id = json_integer_value(json_object_get(json, "guild_id"));
	voice_state->channel_id = json_integer_value(json_object_get(json, "channel_id"));
	voice_state->user_id = json_integer_value(json_object_get(json, "user_id"));
	
	if((buf = json_object_get(json, "member")) != NULL)
	{
		voice_state->member = malloc(sizeof(struct member));
		json_to_member(buf, voice_state->member);
	}

	voice_state->session_id = json_string_value(json_object_get(json, "session_id"));
	
	if(json_is_true(json_object_get(json, "deaf")))
		voice_state->deaf = true;

	if(json_is_true(json_object_get(json, "mute")))
		voice_state->mute = true;

	if(json_is_true(json_object_get(json, "self_deaf")))
		voice_state->self_deaf = true;

	if(json_is_true(json_object_get(json, "self_mute")))
		voice_state->self_mute = true;

	if(json_is_true(json_object_get(json, "suppress")))
		voice_state->suppress = true;
}

void json_to_voice_region(json_t *json, struct voice_region *voice_region)
{
	voice_region->id = json_string_value(json_object_get(json, "id"));
	voice_region->name = json_string_value(json_object_get(json, "name"));

	if(json_is_true(json_object_get(json, "vip")))
		voice_region->vip = true;

	if(json_is_true(json_object_get(json, "optimal")))
		voice_region->optimal = true;

	if(json_is_true(json_object_get(json, "deprecated")))
		voice_region->deprecated = true;

	if(json_is_true(json_object_get(json, "custom")))
		voice_region->custom = true;
}

/*
 * webhook.h
 */

void json_to_webhook(json_t *json, struct webhook *webhook)
{
	json_t *buf;

	webhook->id = json_integer_value(json_object_get(json, "id"));
	webhook->guild_id = json_integer_value(json_object_get(json, "guild_id"));
	webhook->channel_id = json_integer_value(json_object_get(json, "channel_id"));

	if((buf = json_object_get(json, "user")))
	{
		webhook->user = malloc(sizeof(struct user));
		json_to_user(buf, webhook->user);
	}

	webhook->name = json_string_value(json_object_get(json, "name"));
	webhook->avatar = json_string_value(json_object_get(json, "avatar"));
	webhook->token = json_string_value(json_object_get(json, "token"));
}
