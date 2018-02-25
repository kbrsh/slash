# Platform-based mode
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
  MODE := elf64
else ifeq ($(UNAME_S),Darwin)
  MODE := macho64
endif

# Commands
CC := clang
AS := nasm

# Compiler options
CFLAGS := -Wall -I include/
ASFLAGS := -f $(MODE)

# Target files
TARGETS := test benchmark avalanche graph noise noise2D

# All
all: slash.o $(TARGETS)

# Slash
slash.o: src/slash.asm
	$(AS) $(ASFLAGS) $^ -o bin/$@

# Targets
$(TARGETS): %: test/%.c bin/slash.o
	$(CC) $(CFLAGS) $^ -o bin/$@
