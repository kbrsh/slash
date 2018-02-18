# Define the commands
CC := clang
ASM := nasm

# Compiler options
BUILDDIR := build
CFLAGS := -Wall -g
INC := -I include/

slash.o: src/slash.asm
	@echo "  $(ASM) -f elf64 $^ -o $(BUILDDIR)/$@"; $(ASM) -f elf64 $^ -o $(BUILDDIR)/$@

tester: test/tester.c
	@echo "  $(CC) $(CFLAGS) $(INC) $^ build/slash.o -o bin/$@"; $(CC) $(CFLAGS) $(INC) $^ build/slash.o -o bin/$@

benchmark: test/benchmark.c
	@echo "  $(CC) $(CFLAGS) $(INC) $^ build/slash.o -o bin/$@"; $(CC) $(CFLAGS) $(INC) $^ build/slash.o -o bin/$@

avalanche: test/avalanche.c
	@echo "  $(CC) $(CFLAGS) $(INC) $^ build/slash.o -o bin/$@"; $(CC) $(CFLAGS) $(INC) $^ build/slash.o -o bin/$@ -lm

graph: test/graph.c
	@echo "  $(CC) $(CFLAGS) $(INC) $^ build/slash.o -o bin/$@"; $(CC) $(CFLAGS) $(INC) $^ build/slash.o -o bin/$@

all: slash.o tester benchmark avalanche graph
