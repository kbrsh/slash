#include <stdio.h>
#include "../src/slash.h"

#define total 1000

int main() {
	unsigned long long output = 1;
	for (int i = 0; i < total; i++) {
		output = slashInt(output);
		printf("%d	%llu\n", i, output % total);
	}
	return 0;
}
