CC=gcc
CFLAGS=-std=c99
LDFLAGS=
INCLUDE=-Isrc
TARGET=bin/citrus

default: debug
debug: CFLAGS += -g -Wall
debug: target
release: CFLAGS += -O3 -LTO 
release: target
	strip --strip-all $(TARGET)

target: src/main.o src/proc.o src/mem.o src/widget.o src/ui.o
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET) $^ $(LDFLAGS) 

main.o: src/main.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o src/$@

proc.o: src/proc.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o src/$@

mem.o: src/mem.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o src/$@

widget.o: src/widget.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o src/$@

ui.o: src/ui.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o src/$@ 

clean:
	rm src/*.o $(TARGET)
