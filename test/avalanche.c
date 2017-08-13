#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "slash.h"

#define totalKeys 1
#define keySize 8

void generate(unsigned char keys[totalKeys][keySize + 1]) {
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

void avalanche(unsigned char keys[totalKeys][keySize + 1]) {
  unsigned long long results[keySize];
  unsigned char *key;
  unsigned char *flipped = malloc(keySize + 1);
  unsigned long long original;
  for(int i = 0; i < totalKeys; i++) {
    key = keys[i];
    original = slash(key);
    for(int x = 0; x < keySize; x++) {
      printf("%d ", key[x]);
    }
    printf("\n");

    for(int j = 0; j < keySize; j++) {
      strcpy((char*)flipped, (char*)key);
      for(int n = 0; n < 8; n++) {
        flipped[j] = key[j] ^ (1ULL << n);
        for(int x = 0; x < keySize; x++) {
          printf("%d ", flipped[x]);
        }
        printf("\n");
      }
    }
  }
}

int main(void) {
  unsigned char keys[totalKeys][keySize + 1];
  generate(keys);
  avalanche(keys);
  return 0;
}
