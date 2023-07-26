CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
EXEC = shell

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
