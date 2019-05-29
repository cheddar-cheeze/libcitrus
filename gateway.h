typedef enum
{
	DISPATCH,
	HEARTBEAT,
	IDENTIFY,
	STATUS_UPDATE,
	VOICE_STATUS_UPDATE,
	RESUME,
	RECONNECT,
	REQUEST_GUILD_MEMBERS,
	INVALID_SESSION,
	HELLO,
	HEARTBEAT_ACK
} op_code;

//wow need to create the websocket protocol implementation

extern gateway_event_callback();
