#define C1 0xA7F7774CE67BD535ULL
#define C2 0xA7EB2FBAFBB2FA55ULL
#define C3 0xA7CC94E5DD4F7737ULL

#define combine(result, current) result = result ^ (current);

#define mixConstant(result, constant) \
	unsigned long long x1 = result >> 32; \
	unsigned long long x2 = result & 0xFFFFFFFF; \
	unsigned long long x3 = constant >> 32; \
	unsigned long long x4 = constant & 0xFFFFFFFF; \
	unsigned long long x2x4 = x2 * x4; \
	unsigned long long x1x4 = x1 * x4; \
	unsigned long long x2x3 = x2 * x3; \
	unsigned long long x1x3 = x1 * x3; \
	unsigned long long xll = x2x4 & 0xFFFFFFFF; \
	unsigned long long xlh = (x1x4 & 0xFFFFFFFF) + (x2x4 >> 32) + (x2x3 & 0xFFFFFFFF); \
	unsigned long long xhl = (x1x4 >> 32) + (x1x3 & 0xFFFFFFFF) + (x2x3 >> 32) + (xlh >> 32); \
	unsigned long long xhh = x1x3 >> 32; \
	xlh = xlh & 0xFFFFFFFF; \
	unsigned long long xl = xll + (xlh << 32); \
	unsigned long long xh = xhl + (xhh << 32); \
	result = xl ^ xh;

#define mix(result) \
	{ \
		mixConstant(result, C1); \
	} \
	{ \
		mixConstant(result, C2); \
	} \
	{ \
		mixConstant(result, C3); \
	}

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
