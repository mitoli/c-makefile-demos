CC = gcc
CFLAGS =
WARNING = -Wall -Wextra

TARGETS = $(patsubst %.c, %, $(wildcard *.c))

all: $(TARGETS)

%: %.cc
	$(CC) $(CFLAGS) $(WARNING) $@.c -o $@

.PHONY: all clean

clean:
	rm -f $(TARGETS) *.o *.d
