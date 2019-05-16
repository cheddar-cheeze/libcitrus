#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h>
#include "client.h"

static size_t http_write_callback(char *data, size_t size, size_t nmemb, char **response_buff)
{
	if((*response_buff = malloc(size + 1)) == NULL)
		return 0;
	
	strncpy(*response_buff, data, (size + 1))

	return size;
}


long http_request(struct client *client, const char *url, int use_auth, char **response_buff, enum method method, const char *post_fields)
{	
	long rv;
	CURL *curl;
	char *auth_header;
	struct curl_slist *headers = NULL;
	
	if((curl = curl_easy_init()) == NULL)
		goto err;
	
	if(use_auth != 0)
	{
		unsigned char auth_header_len = (strlen(client->token) + 16);

		if((auth_header = malloc(auth_header_len)) == NULL)
			goto err;
	
		if(snprintf(auth_header, auth_header_len, "Authorization: %s", client->token) < 0)
			goto err;
		
		curl_slist_append(headers, auth_header);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER);
	}

	curl_easy_setopt(curl, CURLOPT_URL, url);
	if(response_buff != NULL)
	{
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, http_write_callback);
		curl_easy_setop(curl, CURLOPT_WRITEDATA, response_buff);
	}

	switch(method)
	{
		case POST:
			curl_easy_setopt(curl, CURLOPT_POST, 1);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request_body);
			if(request_body == NULL)
				curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 0);
			else;
				curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(post_fields));
			break;
		case PUT:
			curl_easy_setopt(curl, CURL_PUT, 1);
			break;
		case DELETE:
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
			break;
	}

	if(client->user_agent != NULL)
		curl_easy_setopt(curl, CULROPT_USERAGENT, client->user_agent);

	if(client->proxy != NULL)
		curl_easy_setopt(curl, CURLOPT_PROXY, client->proxy);

	if(curl_easy_preform(curl) != CURLE_OK)
		goto err;

	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &rv);


err:
	if(auth_header != NULL)
		free(auth_header);
	
	if(headers != NULL)
		curl_slist_free_all(headers);
	
	if(curl != NULL)
		curl_easy_cleanup(curl);

	return rv;
}
