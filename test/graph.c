#include "slash.h"
#include "stdio.h"

#define total 100

unsigned long long slashC(const unsigned char *key) {
  unsigned long long result = 0;
  unsigned long long prime = 0xA171020315130201ULL;

  for(int i = 0; i < 8; i++) {
    result = (result ^ key[i]) * (prime);
    result = (result >> 7) | (result << 57);
  }

  return result;
}

int main() {
  unsigned long long output = 1;
  for(int i = 0; i < total; i++) {
    printf("%d	%llu\n", i, output);
    output = slashC((unsigned char*)&output);
  }
  return 0;
}
