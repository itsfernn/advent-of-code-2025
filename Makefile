# Find all folders that contain main.c
DIRS := $(shell find . -type f -name "main.c" -printf "%h\n")
TARGETS := $(DIRS:%=%/main)

CC = gcc
CFLAGS = -O2 -Wall

all: $(TARGETS)

# Build rule: folder/main.x from folder/main.c
%/main: %/main.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)

.PHONY: all clean

