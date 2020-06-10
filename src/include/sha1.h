#ifndef _SHA1_H_
# define _SHA1_H_

# include <stdint.h>

# ifndef BITS_IN_BYTE
#  define BITS_IN_BYTE 8
# endif

# define BITS_IN_BLOCK 512
# define BITS_IN_LEN 64
# define BYTES_IN_BLOCK (BITS_IN_BLOCK / BITS_IN_BYTE)
# define BYTES_IN_LEN (BITS_IN_LEN / BITS_IN_BYTE)
# define BYTES_IN_WORD 4
# define WORDS_IN_HASH 5
# define HASH_LEN (WORDS_IN_HASH * BYTES_IN_WORD)
# define STAGES 4
# define ITERATIONS (HASH_LEN * STAGES)

uint32_t	 func1(uint32_t m, uint32_t l, uint32_t k);
uint32_t	 func2(uint32_t m, uint32_t l, uint32_t k);
uint32_t	 func3(uint32_t m, uint32_t l, uint32_t k);
uint32_t	 func4(uint32_t m, uint32_t l, uint32_t k);

template<typename T>
T			cycleLeftShift(T item, unsigned int n);
void		div_to_blocks(uint8_t *ptr, int size, uint8_t **blocks, const int blocksNum);
uint8_t		*sha1(uint8_t *ptr, int size);

extern uint32_t g_h[WORDS_IN_HASH];
extern const uint64_t g_k[STAGES];
extern uint32_t (*const g_f[STAGES])(uint32_t, uint32_t, uint32_t);

#endif
