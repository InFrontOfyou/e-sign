#include "sha1.h"
#include <cstring>

uint32_t g_h[WORDS_IN_HASH] =
{
	0x67452301u,
	0xEFCDAB89u,
	0x98BADCFEu,
	0x10325476u,
	0xC3D2E1F0u
};	
const uint64_t g_k[STAGES] =
{
	0x5A827999u,
	0x6ED9EBA1u,
	0x8F1BBCDCu,
	0xCA62C1D6u
};
uint32_t (*const g_f[STAGES])(uint32_t, uint32_t, uint32_t) = {
	func1,
	func2,
	func3,
	func4
};

template<typename T>
T cycleLeftShift(T item, unsigned int n)
{
	n %= sizeof(T) * BITS_IN_BYTE;
	return item << n | ((item >> (sizeof(T) * BITS_IN_BYTE - n)) & ~(~(T)0 << n));
}

uint32_t func1(uint32_t m, uint32_t l, uint32_t k)
{
	return (m & l) | (~m & k);
}

uint32_t func2(uint32_t m, uint32_t l, uint32_t k)
{
	return m ^ l ^ k;
}

uint32_t func3(uint32_t m, uint32_t l, uint32_t k)
{
	return (m & l) | (m & k) | (l & k);
}

uint32_t func4(uint32_t m, uint32_t l, uint32_t k)
{
	return m ^ l ^ k;
}

void div_to_blocks(uint8_t *ptr, int size, uint8_t blocks[][BYTES_IN_BLOCK], const int blocksNum)
{
	blocks[size / BYTES_IN_BLOCK][size % BYTES_IN_BLOCK] = (uint8_t)1 << (BITS_IN_BYTE - 1);

	int j = size;
	while (++j < blocksNum * BYTES_IN_BLOCK - BYTES_IN_LEN)
		blocks[j / BYTES_IN_BLOCK][j % BYTES_IN_BLOCK] = 0;

	for (int k = 0; k < BYTES_IN_LEN; ++k)
		blocks[(j + k) / BYTES_IN_BLOCK][(j + k) % BYTES_IN_BLOCK] = ((uint64_t)(size * BITS_IN_BYTE) >> ((BYTES_IN_LEN - 1 - k) * (BITS_IN_BYTE))) & 0xFFu;
	while (--size >= 0)
		blocks[size / BYTES_IN_BLOCK][size % BYTES_IN_BLOCK] = ptr[size];
}

uint8_t *sha1(uint8_t *ptr, int size)
{
	const int blocksNum = (size + BYTES_IN_LEN + 1) / BYTES_IN_BLOCK + ((size + BYTES_IN_LEN + 1) % BYTES_IN_BLOCK > 0);
	uint8_t blocks[blocksNum][BYTES_IN_BLOCK];
	div_to_blocks(ptr, size, blocks, blocksNum);

	uint32_t h[WORDS_IN_HASH];
	std::memcpy(h, g_h, sizeof(uint32_t) * WORDS_IN_HASH);

	for (int n = 0; n < blocksNum; ++n)
	{
		uint32_t w[ITERATIONS];

		uint32_t a = h[0];
		uint32_t b = h[1];
		uint32_t c = h[2];
		uint32_t d = h[3];
		uint32_t e = h[4];

		int t = 0;
		while (t < ITERATIONS)
		{
			if (t < BYTES_IN_BLOCK / BYTES_IN_WORD)
			{
				w[t] = 0;
				for (int size = 0; size < BYTES_IN_WORD; ++size)
					w[t] |= blocks[n][t * BYTES_IN_WORD + size] << ((BYTES_IN_WORD - 1 - size) * BITS_IN_BYTE);
			}
			else
				w[t] = cycleLeftShift<uint32_t>(w[t - 3] ^ w[t - 8] ^ w[t - 14] ^ w[t - 16], 1);
			uint32_t temp = cycleLeftShift<uint32_t>(a, 5) + g_f[t / (ITERATIONS / STAGES)](b, c, d) + e + w[t] + g_k[t / (ITERATIONS / STAGES)];
			e = d;
			d = c;
			c = cycleLeftShift<uint32_t>(b, 30);
			b = a;
			a = temp;
			++t;
		}

		h[0] += a;
		h[1] += b;
		h[2] += c;
		h[3] += d;
		h[4] += e;
	}

	uint8_t *hash = new uint8_t[HASH_LEN];
	
	for (int size = 0; size < WORDS_IN_HASH; ++size)
		for (int j = 0; j < BYTES_IN_WORD; ++j)
			hash[size * BYTES_IN_WORD + (BYTES_IN_WORD - 1 - j)] = (h[size] >> (j * BITS_IN_BYTE)) & 0xFFu;

	return hash;
}
