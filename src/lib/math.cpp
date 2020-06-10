#include "math.h"

t_ull fast_power(t_ull n, t_ull p)
{
	t_ull i = (t_ull)1 << (sizeof(p) * BITS_IN_BYTE - 1);
	t_ull res = 1;

	while (i > 0)
	{
		res = res * res;
		if (p & i)
			res = res * n;
		i >>= 1;
	}
	return res;
}


t_ull fast_module_power(t_ull n, t_ull p, t_ull m)
{
	t_ull i = (t_ull)1 << (sizeof(p) * BITS_IN_BYTE - 1);
	t_ull res = 1;

	while (i > 0)
	{
		res = res * res % m;
		if (p & i)
			res = res * n % m;
		i >>= 1;
	}
	return res;
}

// Modular Multiplicative Inverse
t_ull mmi(t_ull mod, t_ull e)
{
	t_gcd res = gcd_optimized((t_gcd){mod, 1, 0}, (t_gcd){e, 0, 1});
	return MOD(res.v, (t_lli)mod);
}

t_gcd gcd_optimized(t_gcd a, t_gcd b)
{
	int div;

cycle:

	if (b.n == 0)
		return a;
	div = a.n / b.n;
	// mod = a.n % b.n;
	// a.n = div * b.n + mod
	// по алгоритму евклида a.n должно замениться на mod
	// mod = a.n - div * b.n
	// a.n присваеваем a.n - div * b.n
	// то есть из a.n вычитаем div * b.n
	// сделаем это и для коэффициентов тоже
	a.n -= div * b.n;
	a.u -= div * b.u;
	a.v -= div * b.v;
	
	if (a.n == 0)
		return b;
	div = b.n / a.n;
	b.n -= div * a.n;
	b.u -= div * a.u;
	b.v -= div * a.v;
	
	goto cycle;
}

t_ull eulers_func(t_ull n)
{
	std::vector<t_prime> *primes = found_primes(n);

	t_ull res = 1;
	t_ull buf;
	for (t_prime &p : *primes)
	{
		printf("%llu, %d\n", p.prime, p.count);
		buf = fast_power(p.prime, p.count - 1);
		res *= buf * p.prime - buf;
	}
	return res;
}

std::vector<t_prime> *found_primes(t_ull n)
{
	std::vector<t_prime> *primes = new std::vector<t_prime>();
	t_prime p = (t_prime){2, 0};

cycle:

	if (p.prime * p.prime > n)
	{
		primes->push_back((t_prime){n, 1});
		return primes;
	}
	if (n % p.prime == 0)
	{
		while (n % p.prime == 0)
		{
			n /= p.prime;
			++p.count;
		}
		primes->push_back(p);
		if (n == 1)
			return primes;
		++p.prime;
		p.count = 0;
	}
	else
		++p.prime;

	goto cycle;
}
