#include <bits/stdc++.h>
constexpr int mod = 998244353, L = 187, N = 100, K = 4;
inline int qpow(int n, int k) {
	int res = 1;
	for (; k; k >>= 1, n = 1ll * n * n % mod)
		if (k & 1) res = 1ll * n * res % mod;
	return res;

}
std::vector <int> lagrange(const std::vector <int> &x, const std::vector <int> &y) {
	int n = x.size();
	std::vector <int> a(n, 0), b(n + 1, 0), c(n + 1, 0), f(n, 0);
	for(int i = 0; i < n; ++i) {
		int A = 1;
		for(int j = 0; j < n; ++j) if(i != j)
			A = 1ll * A * (x[i] - x[j] + mod) % mod;
		a[i] = 1ll * qpow(A, mod - 2) * y[i] % mod;
	}
	b[0] = 1;
	for(int i = 0; i < n; ++i) {
		for(int j = i + 1; j >= 1; --j)
			b[j] = (1ll * b[j] * (mod - x[i]) + b[j - 1]) % mod;
		b[0] = 1ll * b[0] * (mod - x[i]) % mod;
	}
	for(int i = 0; i < n; ++i) {
		int iv = qpow(mod - x[i], mod - 2);
		if(!iv) {
			for(int j = 0; j < n; ++j) c[j] = b[j + 1];
		} else {
			c[0] = 1ll * b[0] * iv % mod;
			for(int j = 1; j <= n; ++j)
				c[j] = 1ll * (b[j] + mod - c[j - 1]) * iv % mod;
		}
		for(int j = 0; j < n; ++j)
			f[j] = (f[j] + 1ll * a[i] * c[j] % mod) % mod;
	}
	f.resize(N);
	return f;
}
std::vector<int> Encode(std::vector<int> vec) {
	std::vector<int> res;
	for (int x = 0; x < L; ++x) {
		int ans = 0, cur = 1;
		for (int i = 0; i < N; ++i) {
			(ans += 1ll * vec[i] * cur % mod) %= mod;
			cur = 1ll * cur * x % mod;
		}
		assert(ans >= 0 && ans < mod);
		for (int i = 0; i < K; ++i) res.emplace_back(ans);
	}
	return res;
}
std::vector<int> Decode(std::vector<int> vec) {
	std::vector<int> _x, _y;
	for (int x = 0; x < L; ++x) {
		int v = -1;
		for (int i = 4 * x; i < 4 * (x + 1); ++i)
			for (int j = i + 1; j < 4 * (x + 1); ++j)
				if (vec[i] == vec[j]) v = vec[i];
		if (v != -1) _x.emplace_back(x), _y.emplace_back(v);
	}
    return lagrange(_x, _y);
}