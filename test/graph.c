#include <stdio.h>
#include "slash.h"

#define total 1000

unsigned long long slashRandom(const unsigned long long key) {
  unsigned long long result = key * 0xA01731A5AC74E8DBULL;
  return (result >> 8) | (result << 56);
}

int main() {
  unsigned long long output = 1;
  for(int i = 0; i < total; i++) {
    output = slashRandom(output);
    printf("%d	%llu\n", i, output % total);
  }
  return 0;
}
