#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>
#include "channel.h"
#include "client.h"

struct channel *get_channel(struct client *client, unsigned long long channel_id)
{
	struct channel *rv;
	char *url;
	long resp_code;
	char *response_buff;

	if((url = malloc(60)) == NULL)
		goto err;

	if(snprintf(buff, 60, "https://discordapp.com/apiv/v6/channels/%llu", channel_id) < 0)
		goto err;

	resp_code = http_request(client, url, 1, &response_buff, GET, NULL)
	if(	resp_code >= 400)
			goto err;

err:
	if(url != NULL)
		free(url);

	return rv;
}
