struct voice_state
{
	unsigned long long guild_id;
	unsigned long long channel_id;
	unsigned long long user_id;
	struct member *member;
	char *session_id;
	unsigned char deaf;
	unsigned char mute;
	unsigned char self_deaf;
	unsigned char self_mute;
	unsigned char suppress;
};

struct voice_region
{
	char *id;
	char *name;
	unsigned char vip;
	unsigned char optimal;
	unsigned char depr;
	unsigned char custom;
};

struct voice_region *list_voice_regions(void);
