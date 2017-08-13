#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "slash.h"

#define totalKeys 50000
#define keySize 64

unsigned long long slashC(const unsigned char *key) {
  unsigned long long result = 1;
  unsigned long long prime = 0xA171020315130201ULL;
  unsigned long long current;

  while((current = *key++) != '\0') {
    result = (result * prime) ^ (current);
    result = (result >> 7) | (result << 57);
  }

  return result;
}

void generate(unsigned char keys[totalKeys][keySize+1]) {
  srand(clock());

  for(int i = 0; i < totalKeys; i++) {
    for(int j = 0; j < keySize; j++) {
      keys[i][j] = (unsigned char)((rand() % 254) + 1);
    }

    keys[i][keySize] = '\0';

    for(int n = 0; n < (i - 1); n++) {
      if(strcmp((char*)keys[n], (char*)keys[i]) == 0) {
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
  double mean = 0;

  for(int i = 0; i < totalKeys; i++) {
    mean += amount[i];
  }

  return mean / totalKeys;
}

unsigned long long mean(unsigned long long amount[totalKeys]) {
  unsigned long long mean = 0;

  for(int i = 0; i < totalKeys; i++) {
    mean += amount[i];
  }

  return mean / totalKeys;
}

void test(const char *name, unsigned char keys[totalKeys][keySize+1], unsigned long long (*hash)(const unsigned char *key)) {
  clock_t secondsStart, secondsEnd;
  double seconds[totalKeys];

  unsigned long long cyclesStart, cyclesEnd;
  unsigned long long cycles[totalKeys];

  unsigned long long results[totalKeys]__attribute__((unused));

  for(int i = 0; i < totalKeys; i++) {
    secondsStart = clock();
    cyclesStart = rdtsc();

    results[i] = hash(keys[i]);

    secondsEnd = clock();
    cyclesEnd = rdtsc();

    seconds[i] = (secondsEnd - secondsStart) / ((unsigned long long)CLOCKS_PER_SEC / 1000000);
    cycles[i] = cyclesEnd - cyclesStart;
  }

  printf("%s\n  took %.3fμs\n  %llu cycles per hash\n\n", name, doubleMean(seconds), mean(cycles));
}

int main(void) {
  unsigned char keys[totalKeys][keySize+1];
  generate(keys);

  printf("Benchmarking by hashing %d keys with a size of %d bytes\n\n", totalKeys, keySize);

  test("Slash", keys, slash);
  test("Slash (C Implementation)", keys, slashC);
  return 0;
}
