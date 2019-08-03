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

void json_to_channel(json_t *json, struct channel *channel);
void json_to_message(json_t *json, struct message *message);
void json_to_activity(json_t *json, struct activity *activity);
void json_to_application(json_t *json, struct application *application);
void json_to_mention(json_t *json, struct mention *mention);
void json_to_reaction(json_t *json, struct reaction *reaction);
void json_to_overwrite(json_t *json, struct overwrite *overwrite);
void json_to_embed(json_t *json, struct embed *embed);
void json_to_embed_thumbnail(json_t *json, struct embed_thumbnail *embed_thumbnail);
void json_to_embed_video(json_t *json, struct embed_video *embed_video);
void json_to_embed_imgae(json_t *json, struct embed_image *embed_image);
void json_to_embed_provider(json_t *json, struct embed_provider *embed_provider);
void json_to_embed_author(json_t *json, struct embed_author *embed_author);
void json_to_embed_footer(json_t *json, struct embed_footer *embed_footer);
void json_to_embed_field(json_t *json, struct embed_field *embed_field);
void json_to_attachment(json_t *json, struct attachment *attachment);
void json_to_emoji(json_t *json, struct emoji *emoji);
void json_to_guild(json_t *json, struct guild *guild);
void json_to_presence(json_t *json, struct presence *presence);
void json_to_member(json_t *json, struct member *member);
void json_to_integration(json_t *json, struct integration *integration);
void json_to_integration_account(json_t *json, struct integration_account *integration_account);
void json_to_ban(json_t *json, struct ban *ban);
void json_to_invite(json_t *json, struct invite *invite);
void json_to_invite_meta(json_t *json, struct invite_meta *invite_meta);
void json_to_user(json_t *json, struct user *user);



#endif
