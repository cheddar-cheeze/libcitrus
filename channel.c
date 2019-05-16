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
	json_error_t json_err;

	if((url = malloc(60)) == NULL)
		goto err;

	if(snprintf(buff, 60, "https://discordapp.com/apiv/v6/channels/%llu", channel_id) < 0)
		goto err;

	resp_code = http_request(client, url, 1, &response_buff, GET, NULL)
	if(respcode < 200 || resp_code >= 400)
			goto err;

	if((json_err = json_loads(response_buff, 0, json_err)) == NULL)
		goto err;

	//wow k
err:
	if(url != NULL)
		free(url);

	return rv;
}
