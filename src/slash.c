#define combine(result, current) result = result ^ (current);

#define mix(result) \
	result = (box[result & 0xFF]) | (box[(result >> 8) & 0xFF] << 8) | (box[(result >> 16) & 0xFF] << 16) | (box[(result >> 24) & 0xFF] << 24) | (box[(result >> 32) & 0xFF] << 32) | (box[(result >> 40) & 0xFF] << 40) | (box[(result >> 48) & 0xFF] << 48) | (box[(result >> 56) & 0xFF] << 56); \
	\
	result = result * 0xA78ACE24B25835F3ULL; \
	result = result ^ (result >> 56); \
	result = result * 0xA785A2A2D742E537ULL;

unsigned long long box[256] = {158, 163, 200, 235, 223, 47, 250, 35, 101, 191, 5, 132, 161, 71, 142, 18, 7, 133, 176, 253, 246, 207, 117, 233, 138, 92, 74, 16, 187, 10, 91, 249, 94, 210, 80, 167, 13, 136, 202, 150, 62, 126, 160, 162, 186, 22, 108, 124, 112, 21, 232, 14, 148, 127, 218, 143, 214, 220, 39, 57, 190, 144, 159, 130, 88, 2, 154, 242, 81, 24, 111, 147, 66, 54, 238, 28, 37, 63, 45, 153, 169, 102, 208, 247, 226, 48, 79, 27, 183, 145, 184, 228, 180, 89, 56, 20, 11, 170, 40, 84, 152, 198, 55, 103, 237, 221, 178, 174, 8, 29, 90, 122, 205, 155, 12, 67, 30, 96, 243, 43, 254, 26, 44, 15, 193, 251, 59, 4, 78, 129, 137, 31, 203, 1, 219, 70, 181, 236, 157, 72, 225, 104, 194, 222, 53, 0, 241, 85, 131, 192, 6, 9, 114, 46, 248, 95, 240, 121, 128, 244, 239, 107, 19, 201, 25, 149, 116, 105, 34, 175, 76, 224, 146, 51, 139, 41, 75, 204, 52, 23, 171, 68, 196, 164, 50, 77, 245, 229, 134, 106, 252, 217, 115, 33, 188, 97, 61, 227, 86, 87, 82, 32, 166, 17, 98, 93, 60, 231, 140, 172, 125, 195, 212, 206, 73, 177, 3, 69, 58, 199, 118, 141, 209, 197, 109, 173, 123, 211, 135, 189, 151, 110, 213, 83, 38, 113, 216, 119, 179, 99, 36, 42, 120, 255, 185, 64, 168, 230, 49, 234, 165, 65, 156, 215, 182, 100};

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
