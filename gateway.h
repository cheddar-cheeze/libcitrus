#ifndef gateway_h
#define gateway_h

enum op_code
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
};

//wow need to create the websocket protocol implementation

extern gateway_event_callback();
#endif
