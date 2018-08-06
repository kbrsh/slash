#include <stdio.h>
#include "../src/slash.h"

unsigned int passed;
unsigned int failed;

void expect(unsigned long long num1, unsigned long long num2, char *message) {
	// Assert equality of numbers
	if (num1 == num2) {
		passed++;
		printf("\x1b[32m✓ \x1b[0m%s\n", message);
	} else {
		failed++;
		printf("\x1b[31m❌ \x1b[0m%s\nExpected %llx to equal %llx\n", message, num1, num2);
	}
}

int main(void) {
	// Verification Test
	unsigned char bytes[255];
	unsigned char results[255 * 8];

	for (int i = 0; i < 255; i++) {
		bytes[i] = (const unsigned char)i + 1;
		*(unsigned long long*)&results[i * 8] = slash(bytes, i + 1);
	}

	unsigned long long verification = slash(results, 255 * 8);
	unsigned long long expected = 0x29602ce813729476ULL;
	expect(verification, expected, "Should Pass Verification Test");

	if (failed == 0) {
		printf("\n\x1b[32mSuccess\x1b[0m %d Tests Passing\n", passed);
		return 0;
	} else {
		printf("\n\x1b[31mFail\x1b[0m %d Tests Failing, %d Tests Passing\n", failed, passed);
		return 1;
	}
}
