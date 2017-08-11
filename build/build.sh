# Compile and Run Tests
/usr/local/bin/nasm -f macho64 src/slash.asm -o src/slash.o
gcc -Wall test/test.c src/slash.o -o test/test -I ./include
./test/test

# Compile and Run Benchmarks
gcc -Wall test/benchmark.c src/slash.o -o test/benchmark -I ./include
./test/benchmark
