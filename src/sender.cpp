#include "print.h"
#include "math.h"
#include "sha1.h"
#include "rsa.h"
#include "read.h"

int		main(int ac, char *av[])
{
	if (ac != 2)
	{
		printf("usage:\n\t%s [document_name]\n", *av);
		return 0;
	}
	char *str;
	int fd = open(av[1], O_RDONLY);
	ssize_t len = read_text(fd, &str);
	close(fd);
	uint8_t *hash = sha1((uint8_t *)str, len);

	len = HASH_LEN / WORD_LEN + (HASH_LEN % WORD_LEN > 0);
	t_ull nums[len];
	bzero(nums, sizeof(t_ull) * len);
	for(int i = 0; i < HASH_LEN; ++i)
		nums[i / WORD_LEN] |= hash[i] << ((WORD_LEN - 1 - (i % WORD_LEN)) * BITS_IN_BYTE);

	t_ull p = 3557ull;
	t_ull q = 2579ull;
	t_ull n = p * q;
	t_ull coprime_nbr = (p - 1) * (q - 1);
	t_ull public_key = 1007;
	t_ull private_key = mmi(coprime_nbr, public_key);
	int i;
	printf("%llu %llu\n", public_key, n);

	crypt(nums, len, private_key, n);
	for (i = 0; i < len - 1; ++i)
		printf("%llu ", nums[i]);
	printf("%llu\n", nums[i]);
	delete str;
	delete hash;
	return 0;
}
