# Simple C-only Advent of Code Makefile
CC      := gcc
CFLAGS  := -O2 -Wall -std=c11

# find all a.c / b.c under puzzle*/
SOURCES := $(wildcard puzzle*/[ab].c)
BINARIES := $(SOURCES:.c=)

.PHONY: all run clean

all: $(BINARIES)

# compile puzzleXX/a from puzzleXX/a.c (and same for b)
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# run a specific part:
# make run puzzle=03 part=a
run:
	@if [ -z "$(puzzle)" ] || [ -z "$(part)" ]; then \
		echo "Usage: make run puzzle=03 part=a"; \
		exit 1; \
	fi; \
	BIN="puzzle$(puzzle)/$(part)"; \
	SRC="$$BIN.c"; \
	if [ ! -f "$$SRC" ]; then \
		echo "No source: $$SRC"; \
		exit 1; \
	fi; \
	$(MAKE) "$$BIN"; \
	echo "---- Running $$BIN ----"; \
	./$$BIN

# remove compiled binaries (keeps .c files)
clean:
	@if [ -n "$(BINARIES)" ]; then rm -f $(BINARIES); fi

