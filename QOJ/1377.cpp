#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	constexpr int U = 1 << 9, L = 2520;
	using i64 = long long;
	std::vector<int> lt(U, 1);
	for (int S = 1; S < U; ++S) {
		int i = std::__lg(S & (-S));
		lt[S] = std::lcm(lt[S ^ (1 << i)], i + 1);
	}
	auto Calc = [&](i64 n) {
		std::vector<int> d;
		for (; n; n /= 10) d.emplace_back(n % 10);
		int m = d.size();
		std::vector f(U, std::vector(L, 0ll));
		auto _ = f;
		auto Trans = [&]() {
			auto g = f;
			f = _;
			for (int S = 0; S < U; ++S)
				for (int p = 0; p < L; ++p)
					for (int i = 1; i <= 9; ++i)
						f[S | (1 << (i - 1))][(p * 10 + i) % L] += g[S][p];
		};
		auto Get = [&]() {
			i64 ret = 0;
			for (int S = 0; S < U; ++S)
				for (int p = 0; p < L; p += lt[S]) ret += f[S][p];
			return ret;
		};
		f[0][0] = 1;
		i64 ret = 0;
		for (int i = 1; i < m; ++i) {
			Trans();
			ret += Get();
		}
		f = _;
		for (int i = m - 1, mask = 0; i >= 0; --i) {
			Trans();
			if (mask == -1) continue;
			for (int j = 1; j < d[i]; ++j) ++f[mask | (1 << (j - 1))][(n * 10 + j) % L];
			n = n * 10 + d[i];
			if (d[i] == 0) mask = -1;
			else mask |= (1 << (d[i] - 1));
		}
		return ret + Get();
	};
	i64 l, r;
	std::cin >> l >> r;
	std::cout << Calc(r + 1) - Calc(l) << '\n';
	return 0;
}