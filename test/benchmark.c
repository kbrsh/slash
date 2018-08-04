#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../src/slash.h"

#define totalKeys 50000
#define keySize 64

void generate(unsigned char keys[totalKeys][keySize + 1]) {
	// Generate random keys
	srand(clock());

	for (int i = 0; i < totalKeys; i++) {
		for (int j = 0; j < keySize; j++) {
			keys[i][j] = (unsigned char)((rand() % 254) + 1);
		}

		keys[i][keySize] = '\0';

		for (int n = 0; n < (i - 1); n++) {
			if (strcmp((char*)keys[n], (char*)keys[i]) == 0) {
				i--;
				break;
			}
		}
	}
}

static __inline__ unsigned long long rdtsc(void) {
	unsigned hi, lo;
	__asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
	return ((unsigned long long)lo) | (((unsigned long long)hi)<<32);
}

double doubleMean(double amount[totalKeys]) {
	// Get mean of doubles
	double mean = 0;

	for(int i = 0; i < totalKeys; i++) {
		mean += amount[i];
	}

	return mean / totalKeys;
}

unsigned long long mean(unsigned long long amount[totalKeys]) {
	// Get mean of unsigned 64 bit numbers
	unsigned long long mean = 0;

	for(int i = 0; i < totalKeys; i++) {
		mean += amount[i];
	}

	return mean / totalKeys;
}

void test(const char *name, unsigned char keys[totalKeys][keySize + 1], unsigned long long (*hash)(const unsigned char *key, int length)) {
	// Benchmark time and cycles
	clock_t timeStart, timeEnd;
	double times[totalKeys];

	unsigned long long cyclesStart, cyclesEnd;
	unsigned long long cycles[totalKeys];

	unsigned long long results[totalKeys]__attribute__((unused));

	// Time
	for(int i = 0; i < totalKeys; i++) {
		timeStart = clock();
		results[i] = hash(keys[i], keySize);
		timeEnd = clock();

		times[i] = (double)(timeEnd - timeStart) / CLOCKS_PER_SEC;
	}

	// Cycles
	for(int i = 0; i < totalKeys; i++) {
		cyclesStart = rdtsc();
		results[i] = hash(keys[i], keySize);
		cyclesEnd = rdtsc();

		cycles[i] = cyclesEnd - cyclesStart;
	}

	double timesMean = doubleMean(times) * (double)1000000000;
	unsigned long long cyclesMean = mean(cycles);

	printf("%s\n  %.3fns per hash\n  %.3fns per byte\n  %llu cycles per hash\n  %.3f cycles per byte\n\n", name, timesMean, timesMean / (double)keySize, cyclesMean, (double)cyclesMean / (double)keySize);
}

int main(void) {
	unsigned char keys[totalKeys][keySize + 1];
	generate(keys);

	printf("Benchmarking by hashing %d keys with a size of %d bytes\n\n", totalKeys, keySize);

	test("Slash", keys, slash);
	return 0;
}
