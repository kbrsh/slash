#include <stdio.h>
#include "./include/slash.h"

int main(void) {
  const unsigned char *lol = "A";
  printf("%llu", slash(lol));
  // printf("%c", slash(lol));
  return 0;
}
