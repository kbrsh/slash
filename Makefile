# Define the commands
CC := clang
ASM := nasm

# Compiler options
BUILDDIR := build
CFLAGS := -Wall -g
INC := -I include/
MODE :=

# Guess platform
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
  MODE += elf64
else ifeq ($(UNAME_S),Darwin)
  MODE += macho64
endif

# Define the C compiling command
C_COMPILE := $(CC) $(CFLAGS) $(INC) build/slash.o

# Compiling tasks
slash.o: src/slash.asm
	@echo "  $(ASM) -f $(MODE) $^ -o $(BUILDDIR)/$@"; $(ASM) -f $(MODE) $^ -o $(BUILDDIR)/$@

tester: test/tester.c
	@echo "  $(C_COMPILE) $^ -o bin/$@"; $(C_COMPILE) $^ -o bin/$@

benchmark: test/benchmark.c
	@echo "  $(C_COMPILE) $^ -o bin/$@"; $(C_COMPILE) $^ -o bin/$@

avalanche: test/avalanche.c
	@echo "  $(C_COMPILE) $^ -o bin/$@ -lm"; $(C_COMPILE) $^ -o bin/$@ -lm

graph: test/graph.c
	@echo "  $(C_COMPILE) $^ -o bin/$@"; $(C_COMPILE) $^ -o bin/$@

# Combine all tasks
all: slash.o tester benchmark avalanche graph
