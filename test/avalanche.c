#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "slash.h"

#define totalKeys 50000
#define keySize 8
#define bitSize keySize * 8

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

void svg(double results[bitSize][bitSize]) {
  printf("<!DOCTYPE html><html><head><meta charset=\"utf-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><meta name=\"description\" content=\"Slash Avalanche Diagram\"><meta name=\"author\" content=\"Kabir Shah\"><title>Slash | Avalanche</title><link rel=\"stylesheet\" type=\"text/css\" href=\"https://rawgit.com/kbrsh/wing/master/dist/wing.min.css\" /></head><body><div class=\"full-screen center\"><svg width=\"300\" height=\"300\" xmlns=\"http://www.w3.org/2000/svg\">");

  for(int i = 0; i < bitSize; i++) {
    for(int j = 0; j < bitSize; j++) {
      results[i][j] = (results[i][j] / ((double)totalKeys)) * 100.0;
      printf("<rect x=\"%d\" y=\"%d\" width=\"5\" height=\"5\" fill=\"hsl(197, 100%%, %d%%)\"/>", i * 5, j * 5, (int)round(results[i][j]));
    }
  }

  printf("</svg></div></body></html>");
}

void avalanche(unsigned char keys[totalKeys][keySize + 1]) {
  double results[bitSize][bitSize] = {{0.0}};

  unsigned char *key;
  unsigned long long original;

  unsigned char flipped[keySize + 1];
  unsigned long long result;

  unsigned long long diff;

  for(int i = 0; i < totalKeys; i++) {
    key = keys[i];
    original = slash(key);

    for(int j = 0; j < keySize; j++) {
      strcpy((char*)flipped, (char*)key);
      for(int n = 0; n < 8; n++) {
        flipped[j] = key[j] ^ (1U << n);
        result = slash(flipped);
        diff = original ^ result;

        for(int k = 0; k < bitSize; k++) {
          if((diff & 1) != 0) {
            results[(j * 8) + n][k]++;
          }

          diff = diff >> 1;
        }
      }
    }
  }

  svg(results);
}

int main(void) {
  unsigned char keys[totalKeys][keySize + 1];
  generate(keys);
  avalanche(keys);
  return 0;
}
