#ifndef json_h
#define json_h

#include <jansson.h>

#include "channel.h"
#include "emoji.h"
#include "guild.h"
#include "invite.h"
#include "user.h"
#include "voice.h"
#include "webhook.h"

struct channel *json_to_channel(json_t *json, struct channel *rv);
struct message *json_to_message(json_t *json, struct message *rv);
struct reaction *json_to_reaction(json_t *json, struct reaction *rv);
struct overwrite *json_to_overwrite(json_t *json, struct overwrite *rv);
struct embed *json_to_embed(json_t *json, struct embed *rv);
struct attachment *json_to_attachment(json_t *json, struct attachment *rv);
struct emoji *json_to_emoji(json_t *json, struct emoji *rv);
struct guild *json_to_guild(json_t *json, struct guild *rv);
struct member *json_to_member(json_t *json, struct member *rv);
struct integration *json_to_integration(json_t *json, struct integration *rv);
struct integration_account *json_to_integration_account(json_t *json, struct integration_account *rv);
struct ban *json_to_ban(json_t *json, struct ban *rv);
struct invite *json_to_invite(json_t *json, struct invite *rv);
struct invite_meta *json_to_invite_meta(json_t *json, struct invite_meta *rv);
struct user *json_to_user(json_t *json, struct user *rv);



#endif
