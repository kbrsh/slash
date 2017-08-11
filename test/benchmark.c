#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "slash.h"

#define size 50000

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

void generate(unsigned char keys[size][6]) {
  srand(clock());

  for(int i = 0; i < size; i++) {
    for(int j = 0; j < 5; j++) {
      keys[i][j] = (unsigned char)((rand() % 254) + 1);
    }

    for(int n = 0; n < (i - 1); n++) {
      if(strcmp((char*)keys[n], (char*)keys[i]) == 0) {
        i--;
        break;
      }
    }
  }
}

void test(const char *name, unsigned char keys[size][6], unsigned long long (*hash)(const unsigned char *key)) {
  clock_t seconds = clock();
  unsigned long long results[size]__attribute__((unused));

  for(int i = 0; i < size; i++) {
    results[i] = hash(keys[i]);
  }

  printf("%s took %.2fms\n", name, (double)(clock() - seconds)/(CLOCKS_PER_SEC/1000));
}

int main(void) {
  unsigned char keys[size][6];
  generate(keys);

  printf("Benchmarking by hashing %d keys\n\n", size);

  test("Slash", keys, slash);
  test("Slash (C Implementation)", keys, slashC);
  return 0;
}
