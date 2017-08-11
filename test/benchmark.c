#include <stdio.h>
#include <time.h>

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

int main(void) {
  return 0;
}
