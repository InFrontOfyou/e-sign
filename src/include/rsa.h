#ifndef _RSA_H_
# define _RSA_H_

# include "math.h"

# define WORD_LEN 1

static_assert(WORD_LEN > 0, "WORD_LEN cannot be less than or equal to zero");

void	crypt(t_ull *nums, size_t len, t_ull p, t_ull m);

#endif
