#include "rsa.h"

void crypt(t_ull *nums, size_t len, t_ull p, t_ull m)
{
	while (len > 0)
	{
		--len;
		nums[len] = fast_module_power(nums[len], p, m);
	}
}
