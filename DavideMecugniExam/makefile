CC=gcc 
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c11
BIN=$(patsubst %.c,%,$(wildcard *.c))

all: $(BIN)

%: %.c 
	$(CC) $(CFLAGS) -o $@ $<

