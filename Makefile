CC=cc
CFLAGS=-std=c99 -Werror
LDFLAGS=-shared -ljansson -lcurl
TARGET=libcitrus.so

default: debug
debug: CFLAGS += -g
debug: target
release: CFLAGS += -O2 
release: target
	strip --strip-all $(TARGET)

target: auth.o client.o channel.o emoji.o gateway.o guild.o invite.o json.o user.o voice.o webhook.o
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS) 

auth.o: auth.c
	$(CC) $(CFLAGS) -c $^ -o $@

client.o: client.c
	$(CC) $(CFLAGS) -c $^ -o $@

channel.o: channel.c
	$(CC) $(CFLAGS) -c $^ -o $@

emoji.o: emoji.c 
	$(CC) $(CFLAGS) -c $^ -o $@

gateway.o: gateway.c
	$(CC) $(CFLAGS) -c $^ -o $@

guild.o: guild.c
	$(CC) $(CFLAGS) -c $^ -o $@

invite.o: invite.c
	$(CC) $(CFLAGS) -c $^ -o $@

json.o: json.c
	$(CC) $(CFLAGS) -c $^ -o $@

time.o: time.c
	$(CC) $(CFLAGS) -c $^ -o $@

user.o: user.c
	$(CC) $(CFLAGS) -c $^ -o $@

voice.o: voice.c
	$(CC) $(CFLAGS) -c $^ -o $@

webhook.o: webhook.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm *.o $(TARGET)
