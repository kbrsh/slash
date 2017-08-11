# Compile and Run Tests
/usr/local/bin/nasm -f macho64 src/slash.asm -o src/slash.o
gcc -Wall test/test.c src/slash.o -o test/test -I ./include
./test/test
