CC=gcc 
CFLAGS=-Wall -std=c11 
BIN=$(patsubst %.c,%,$(wildcard *.c))

all: $(BIN)

%: %.c 
	$(CC) $(CFLAGS) -o $@ $<