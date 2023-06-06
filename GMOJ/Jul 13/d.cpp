#include <bits/stdc++.h>
int main() {
	const int Mod = 10007;
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m, b, v;
	std::cin >> n >> b >> m >> v;
	--n;
	std::vector<int> ans(1 << b);
	for (int S = 1; S < (1 << b); ++S) {
		std::vector<int> f(m), g(m);
		for (int i = 1; i < b; ++i)
			if (S >> i & 1) f[i % m]++;
		for (int i = 0; i < b; ++i)
			if (S >> i & 1) g[i % m]++;
		for (int N = n, B = b % m; N; N >>= 1) {
			std::vector<int> F(m);
			if (N & 1) {
				for (int i = 0; i < m; ++i)
					for (int j = 0; j < m; ++j)
						(F[(i * B + j) % m] += f[i] * g[j] % Mod) %= Mod;
				f = F;
			}
			F.assign(m, 0);
			for (int i = 0; i < m; ++i)
				for (int j = 0; j < m; ++j)
					(F[(i * B + j) % m] += g[i] * g[j] % Mod) %= Mod;
			g = F;
			B = B * B % m;
		}
		ans[S] = f[v];
		for (int T = (S - 1) & S; T; T = (T - 1) & S)
			ans[S] = (ans[S] - ans[T] + Mod) % Mod;
		for (int i = b - 1; i >= 0; --i)
			if (S >> i & 1) std::cout << i;
		std::cout << ' ' << ans[S] << '\n';
	}
	return 0;
}