#ifndef _MATH_H_
# define _MATH_H_

typedef unsigned long long int  t_ull;
typedef long long int		   t_lli;
typedef struct	s_gcd			t_gcd;
typedef struct	s_prime			t_prime;

#include <vector>

struct			s_gcd
{
	t_ull		n;
	t_lli		u;
	t_lli		v;
};

struct			s_prime
{
	t_ull		prime;
	int			count;
};

# define ABS(x) ((x) >= 0 ? (x) : (-(x)))
# define DIV(n, m) ((n) / (m) - ((n) < 0))
# define MOD(n, m) ((n) - DIV(n, m) * (m))

# ifndef BITS_IN_BYTE
#  define BITS_IN_BYTE 8
# endif

t_ull					fast_power(t_ull n, t_ull p);
t_ull					fast_module_power(t_ull n, t_ull p, t_ull m);
t_ull 					mmi(t_ull mod, t_ull e);
t_gcd					gcd_optimized(t_gcd a, t_gcd b);
t_ull					eulers_func(t_ull n);
std::vector<t_prime>	*found_primes(t_ull n);

#endif
