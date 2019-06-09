struct emoji
{
	unsigned long long id;
	const char *name;
	unsigned long long *roles;
	struct user *user;
	unsigned char req_colons;
	unsigned char managed;
	unsigned char animated;
};

struct emoji *list_guild_emojis(unsigned long long guild_id);
struct emoji *get_guild_emoji(unsigned long long guild_id, unsigned long long emoji_id);
int create_guild_emojie(unsigned long long guild_id, char *name, char *image, void *roles); //find out type of roles param
int modify_guild_emoji(unsigned long long guild_id, unsigned long long emoji_id char *name, void roles); //find out type of roles param
int delete_guild_emoji(unsigned long long  guild_id, unsigned long long emoji_id);

