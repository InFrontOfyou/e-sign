#include "print.h"
#include "math.h"
#include "sha1.h"
#include "rsa.h"
#include "read.h"
#include <ctype.h>

int		main(int ac, char *av[])
{
	if (ac != 2)
	{
		printf("usage:\n\t%s [document_name]\n", *av);
		return 0;
	}
	char *str;
	ssize_t len = read_text(0, &str);

	t_ull n = 0;
	t_ull public_key = 0;

	int i = 0;
	while (i < len && isdigit(str[i]))
		public_key = public_key * 10 + (str[i++] - '0');
	while (i < len && isspace(str[i]))
		++i;
	while (i < len && isdigit(str[i]))
		n = n * 10 + (str[i++] - '0');
	int k = 0;
	for (int j = i; j < len; ++j)
		if (j > 0 && isspace(str[j - 1]) && isdigit(str[j]))
			++k;
	t_ull *nums = new t_ull[k];
	int j = 0;
	while (j < k)
	{
		nums[j] = 0;
		while (i < len && isspace(str[i]))
			++i;
		while (i < len && isdigit(str[i]))
			nums[j] = nums[j] * 10 + (str[i++] - '0');
		++j;
	}
	crypt(nums, k, public_key, n);

	int fd = open(av[1], O_RDONLY);
	len = read_text(fd, &str);
	close(fd);
	uint8_t hash[HASH_LEN];
	for(int i = 0; i < HASH_LEN; ++i)
		hash[i] = nums[i / WORD_LEN] >> ((WORD_LEN - 1 - (i % WORD_LEN)) * BITS_IN_BYTE) & ~(uint8_t)0;
	uint8_t *hash_orig = sha1((uint8_t *)str, len);
	for (int i = 0; i < HASH_LEN; ++i)
		printf("%02x ", hash[i]);
	printf("\nvs\n");
	for (int i = 0; i < HASH_LEN; ++i)
		printf("%02x ", hash_orig[i]);
	printf("\n");
	printf("%d\n", memcmp(hash, hash_orig, HASH_LEN));


	delete str;
	delete hash_orig;
	return 0;
}
