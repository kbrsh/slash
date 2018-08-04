#define combine(result, current) result = result ^ (current);

#define mix(result) \
	result = result * 0xA7EF77A80B732831ULL; \
	result = (result >> 21) | (result << 43); \
	result = result * 0xA7D3A48E08CBE2E3ULL; \
	result = (result >> 22) | (result << 42); \
	result = result * 0xA7F2BF9C29FF7D37ULL; \
	result = (result >> 21) | (result << 43); \
	result = result ^ (((result & 0x1FFFFF) + (result >> 43)) << 21);

unsigned long long slashInt(const unsigned long long key) {
	unsigned long long result = key;
	mix(result);
	return result;
}

unsigned long long slash(const unsigned char* key, int length) {
	unsigned char* data = (unsigned char*)key;
	unsigned long long result = 0;

	while (length >= 8) {
		combine(result, (unsigned long long)data[7] << 56 | (unsigned long long)data[6] << 48 | (unsigned long long)data[5] << 40 | (unsigned long long)data[4] << 32 | (unsigned long long)data[3] << 24 | (unsigned long long)data[2] << 16 | (unsigned long long)data[1] << 8 | (unsigned long long)data[0]);
		mix(result);

		data += 8;
		length -= 8;
	}

	switch (length) {
		case 7: combine(result, (unsigned long long)data[6] << 48);
		case 6: combine(result, (unsigned long long)data[5] << 40);
		case 5: combine(result, (unsigned long long)data[4] << 32);
		case 4: combine(result, (unsigned long long)data[3] << 24);
		case 3: combine(result, (unsigned long long)data[2] << 16);
		case 2: combine(result, (unsigned long long)data[1] << 8);
		case 1: combine(result, (unsigned long long)data[0]);
	}

	mix(result);

	return result;
}
