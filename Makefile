# Commands
CC := gcc-7

# Compiler options
CFLAGS := -Wall -O3
CLIBS := -lm

# Target files
TARGETS := test benchmark avalanche graph noise noise2D

# All
all: slash.o $(TARGETS)

# Slash
slash.o: src/slash.c
	$(CC) $(CFLAGS) -c $^ -o $@

# Targets
$(TARGETS): %: test/%.c
	$(CC) $(CFLAGS) -c $^
	$(CC) $(CFLAGS) slash.o $@.o -o bin/$@ $(CLIBS)

# Clean
.PHONY: clean
clean:
	rm -f *.o bin/*
