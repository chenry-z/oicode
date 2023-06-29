#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, t;
	std::cin >> n >> t;
	std::vector<int> r(n), s(n);
	using f64 = long double;
	std::vector<f64> p(n);
	for (int i = 0; i < n; ++i) std::cin >> r[i] >> s[i] >> p[i];
	std::vector f(t + 1, std::vector(n, f64(0)));
	std::vector g(t + 1, std::vector(1 << n, f64(0)));
	g[0][(1 << n) - 1] = 1;
	for (int i = 0; i < t; ++i) {
		for (int j = 0; j < n; ++j) f[i + 1][j] += f[i][j];
		for (int S = 0; S < (1 << n); ++S) {
			if (g[i][S] == 0) continue;
			int cnt = __builtin_popcount(S);
			f64 sum = 0;
			for (int j = 0; j < n; ++j)
				if (S >> j & 1) sum += f[i][j];
			for (int j = 0; j < n; ++j) {
				if (!(S >> j & 1)) continue;
				f64 P = sum == 0 ? 1. / cnt : f[i][j] / sum;
				if (i + r[j] <= t) g[i + r[j]][S ^ (1 << j)] += g[i][S] * P * (1 - p[j]);
				if (i + r[j] + s[j] <= t) {
					f[i + r[j] + s[j]][j] += g[i][S] * P * p[j];
					g[i + r[j] + s[j]][S ^ (1 << j)] += g[i][S] * P * p[j];
				}
			}
		}
	}
	for (auto c : f[t]) std::cout << std::fixed << std::setprecision(10) << c << '\n';
	return 0;
}