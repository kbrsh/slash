#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "slash.h"

#define totalKeys 1000
#define keySize 64 + 1

void generate(unsigned char keys[totalKeys][keySize]) {
  srand(clock());

  for(int i = 0; i < totalKeys; i++) {
    for(int j = 0; j < keySize; j++) {
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

void avalanche(unsigned char keys[totalKeys][keySize]) {
  for(int i = 0; i < totalKeys; i++) {
    for(int j = 0; j < keySize; j++) {
      printf("%d ", keys[i][j]);
    }
    printf("\n");
  }
}

int main(void) {
  unsigned char keys[totalKeys][keySize];
  generate(keys);
  avalanche(keys);
  return 0;
}
