struct webhook
{
	unsigned long long id;
	unsigned long long guild_id;
	unsigned long long channel_id;
	struct user *user;
	char *name;
	char *avatar;
	char *token;
};

struct webhook *create_webhook(unsigned long long channel_id);
struct webhook *get_guild_webhooks(unsigned long long guild_id);
struct webhook *get_webhook(unsigned long long webhook_id);
struct webhook *get_webhook_wtoken(unsigned long long webhook_id, const char *token);
struct webhook *modify_webhook(unsigned long long webhook_id, const char *name, const char *avatar, unsigned long long channel_id);
struct webhook *modify_webhook_wtoken(unsigned long long webhook_id, const char *name, const char *avatar, unsigned long long channel_id);
struct webhook *delete_webhook(unsigned long long webhook_id);
struct webhook *delete_webhook_wtoken(unsigned long long webhook_id);
int *execute_webhook(unsigned long long webhook_id, const char *token, unsigned char wait, const char *content, const char *username, const char *avatar_url, void *file shit, struct embed *embed, const char *payload_json);
//meh im too lazy to add shit for github/slack webhooks 
