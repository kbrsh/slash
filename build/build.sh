# Compile and run tests
/usr/local/bin/nasm -f macho64 src/slash.asm -o src/slash.o
gcc -Wall test/test.c src/slash.o -o test/test -I ./include
./test/test

# Compile and run benchmarks
gcc -Wall test/benchmark.c src/slash.o -o test/benchmark -I ./include
./test/benchmark

# Compile and run avalanche tests
gcc -Wall test/avalanche.c src/slash.o -o test/avalanche -I ./include
./test/avalanche

# Compile and run chaos grapher
gcc -Wall test/graph.c src/slash.o -o test/graph -I ./include
./test/graph > points.txt

# Compile and run noise generator
gcc -Wall test/noise.c src/slash.o -o test/noise -I ./include
./test/noise > noise.txt
