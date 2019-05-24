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
}


struct message *json_to_message(const char *json)
{
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
