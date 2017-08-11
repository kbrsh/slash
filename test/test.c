#include "stdio.h"

unsigned int passed;
unsigned int failed;

void expect(unsigned long long num1, unsigned long long num2, unsigned char *message) {
  if(num1 == num2) {
    passed++;
    printf("\x1b[32m✓ \x1b[0m%s\n", message);
  } else {
    failed++;
    printf("\x1b[31m❌ \x1b[0m%s\nExpected %llx to equal %llx\n", message, num1, num2);
  }
}

unsigned long long slash(const unsigned char *key) {
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
  // Verification Test
  unsigned char bytes[256] = {'\0'};
  unsigned char results[255 * 8];

  for(int i = 0; i < 255; i++) {
    bytes[i] = (const unsigned char)i + 1;
    *(unsigned long long*)&results[i * 8] = slash(bytes);
  }

  unsigned long long verification = slash(results);
  unsigned long long expected = 0xC5C1D27F4283993AULL;
  expect(verification, expected, "Should Pass Verification Test");

  if(failed == 0) {
    printf("\n\x1b[32mSuccess\x1b[0m %d Tests Passing\n", passed);
  } else {
    printf("\n\x1b[31mFail\x1b[0m %d Tests Failing, %d Tests Passing\n", failed, passed);
  }

  return 0;
}