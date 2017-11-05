# Compile and Run Tests
/usr/local/bin/nasm -f macho64 src/slash.asm -o src/slash.o
gcc -Wall test/test.c src/slash.o -o test/test -I ./include
./test/test

# Compile and Run Benchmarks
gcc -Wall test/benchmark.c src/slash.o -o test/benchmark -I ./include
./test/benchmark

# Compile and Run Avalanche Tests
gcc -Wall test/avalanche.c src/slash.o -o test/avalanche -I ./include
./test/avalanche

# Compile and Run Chaos Grapher
gcc -Wall test/graph.c src/slash.o -o test/graph -I ./include
./test/graph | points.txt
