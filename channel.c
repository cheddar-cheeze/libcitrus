#include <stdio.h>
#include <stdlib.h>

#include "channel.h"
#include "client.h"
#include "json.h"

void channel_free(struct channel *channel)
{
	free(channel->name);
	free(channel->topic);
	for(int x = 0;x < channel->overwrite_count;x++)
		free(channel->overwrites[x]);
	
	free(channel->overwrites);
	for(int x = 0; x < channel->recipient_count;x++)
		user_free(channel->recipients[x]);

	free(channel->recipients);
	free(channel->icon);
	free(channel->last_pin_timestamp);
	free(channel);
#ifdef debug
	fprintf(stderr, "[DEBUG] channel structure %p freed from heap\n", channel);
#endif
}

void message_free(struct message *message)
{
	user_free(message->author);
	member_free(message->member);
	free( message->content);
	free(message->timestamp);
	free(message->edited_timestamp);
	for(int x = 0;x < message->mention_count;x++)
		mention_free(message->mentions[x]);

	free(message->mentions);
	for(int x = 0;x < message->attachment_count;x++)
		attachment_free(message->attachments[x]);

	free(message->attachments);
	for(int x = 0;x< message->embed_count;x++)
		embed_free(message->embeds[x]);
	
	free(message->embeds);
#ifdef debug
	fprintf(stderr, "[DEBUG] message structure %p freed from heap\n", message);
#endif
}

void mention_free(struct mention *mention)
{
	user_free(mention->user);
	member_free(mention->member);
	free(mention);
#ifdef debug
	fprintf(stderr, "[DEBUG] mention structure %p freed from heap\n", mention);
#endif
}

void reaction_free(struct reaction *reaction)
{
	emoji_free(reaction->emoji);
	free(reaction);
#ifdef debug
	fprintf(stderr, "[DEBUG] reaction structure %p freed from heap\n", reaction);
#endif
}

void application_free(struct application *application)
{
	free(application->cover_image);
	free(application->description);
	free(application->icon);
	free(application->name);
	free(application);
#ifdef debug
	fprintf(stderr, "[DEBUG] application structure %p freed from heap\n", application);
#endif
}

void activity_free(struct activity *activity)
{
	free(activity->party_id);
	free(activity);
#ifdef debug
	fprintf(stderr, "[DEBUG] activity structure %p freed from heap\n", activity);
#endif
}

void embed_free(struct embed *embed)
{
	free(embed->title);
	free(embed->type);
	free(embed->description);
	free(embed->url);
	free(embed->timestamp);
	embed_footer_free(embed->footer);
	embed_image_free(embed->image);
	embed_thumbnail_free(embed->thumbnail);
	embed_video_free(embed->video);
	embed_provider_free(embed->provider);
	embed_author_free(embed->author);
	for(int x = 0;x < embed->field_count;x++)
		embed_field_free(embed->fields[x]);

	free(embed->fields);
	free(embed);
#ifdef debug
	fprintf(stderr, "[DEBUG] embed object %p freed from heap\n", embed);
#endif
}

void embed_thumbnail_free(struct embed_thumbnail *embed_thumbnail)
{
	free(embed_thumbnail->url);
	free(embed_thumbnail->proxy_url);
	free(embed_thumbnail);
#ifdef debug
	fprintf(stderr, "[DEBUG] embed thumbnail structure %p freed from heap\n", embed_thumbnail);
#endif
}

void embed_video_free(struct embed_video *embed_video)
{
	free(embed_video->url);
	free(embed_video);
#ifdef debug
	fprintf(stderr, "[DEBUG] embed video struct %p freed from heap\n", embed_video);
#endif
}

void embed_image_free(struct embed_image *embed_image)
{
	free(embed_image->url);
	free(embed_image->proxy_url);
	free(embed_image);
#ifdef debug
	fprintf(stderr, "[DEBUG] embed image structure %p freed from heap\n", embed_image);
#endif
}

void embed_provider_free(struct embed_provider *embed_provider)
{
	free(embed_provider->name);
	free(embed_provider->url);
	free(embed_provider);
#ifdef debug
	fprintf(stderr, "[DEBUG] embed provider structure %p freed from heap\n");
#endif
}

void embed_author_free(struct embed_author *embed_author)
{
	free(embed_author->name);
	free(embed_author->url);
	free(embed_author->icon_url);
	free(embed_author->proxy_icon_url);
	free(embed_author);
#ifdef debug
	fprintf(stderr, "[DEBUG] embed author structure %p freed from heap\n");
#endif
}

void embed_footer_free(struct embed_footer *embed_footer)
{
	free(embed_footer->text);
	free(embed_footer->icon_url);
	free(embed_footer->proxy_icon_url);
	free(embed_footer);
#ifdef debug
	fprintf(stderr, "[DEBUG] embed footer structure %p freed from heap\n");
#endif
}

void embed_field_free(struct embed_field *embed_field)
{
	free(embed_field->name);
	free(embed_field->value);
	free(embed_field);
#ifdef debug
	fprintf(stderr, "[DEBUG] embed field structure %p freed from heap\n");
#endif
}

void attachment_free(struct attachment *attachment)
{
	free(attachment->filename);
	free(attachment->proxy_url);
	free(attachment);
#ifdef debug
	fprintf(stderr, "[DEBUG] attachment structure %p freed from heap\n");
#endif
}



struct channel *get_channel(struct client *client, unsigned long long channel_id)
{
	struct channel *rv = NULL;
	char *buf = malloc(60);
	long resp_code;
	char *response_buf;

	if(snprintf(buf, 60, "https://discordapp.com/apiv/v6/channels/%llu", channel_id) < 0)
	{	
#ifdef debug
		fprintf(stderr, "[DEBUG] Failed to catenate guild_id to url\n");
#endif
		goto err;
	}


	resp_code = http_request(client, buf, 1, &response_buf, GET, NULL);
	if(resp_code >= 400)
	{
#ifdef debug
		fprintf(stderr, "[DEBUG] http request has failed with error code %li\n", resp_code);
#endif
		goto err;
	}
	
	json_error_t *json_error;
	json_t *json = json_loads(response_buf, 0, json_error);
	
	rv = malloc(sizeof(struct channel));
	json_to_channel(json, rv);
	json_decref(json);

err:
	if(buf != NULL)
		free(buf);

	return rv;
}
