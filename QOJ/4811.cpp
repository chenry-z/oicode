#include <bits/stdc++.h>
int suf[200][201], dp[200][201], deg[200];
/*
Warning: TLE
*/
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	std::vector<std::vector<int>> e(n);
	for (int i = 1, u, v; i < n; ++i) {
		std::cin >> u >> v;
		--u, --v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	constexpr int Mod = 998244353;
	std::vector<std::vector<int>> pw(n + 1);
	for (int i = 0; i <= n; ++i)
		for (int j = 1, w = 1; j <= n; ++j, w = 1ll * w * i % Mod)
			pw[i].emplace_back(w);
	// for (int i = 0; i < 200; ++i) deg[i] = 0;
	std::function<void(int, int)> DFS = [&](int u, int fa) {
		if (u != 0 && e[u].size() == 1ull) return;
		for (auto v : e[u])
			if (v != fa) DFS(v, u), ++deg[u];
		int leaves = 0;
		std::vector<int> cnt(n), big;
		for (auto v : e[u]) {
			if (v == fa) continue;
			if (deg[v] == 0) ++leaves;
			else ++cnt[deg[v]];
		}
		for (int i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
		int B = 0;
		for (int i = 0, mn = 1E9; i < n; ++i)
			if (mn > i + cnt[n - 1] - cnt[i]) {
				mn = i + cnt[n - 1] - cnt[i];
				B = i;
			}
		for (auto v : e[u])
			if (v != fa && deg[v] > B) big.emplace_back(v);
		int sz = big.size(), allv = 1 << (B + 1), alls = 1 << sz;
		std::vector f(allv, 0);
		for (int S = 0; S < allv; ++S) {
			f[S] = 1;
			for (auto v : e[u]) {
				if (v == fa || deg[v] == 0 || deg[v] > B) continue;
				int coef = 0;
				for (int i = 0; i <= B; ++i)
					if (!(S >> i & 1)) (coef += dp[v][i]) %= Mod;
				f[S] = 1ll * f[S] * coef % Mod;
			}
		}
		for (int i = 0; i <= B; ++i)
			for (int S = 0; S < allv; ++S)
				if (!(S >> i & 1))
				(f[S] += Mod - f[S | (1 << i)]) %= Mod;
		std::vector g(alls, std::vector(deg[u] + 2, 0));
		std::vector h(alls, 0);
		for (int S = 0; S < allv; ++S) if (f[S] != 0) {
			for (int T = 0; T < alls; ++T)
				for (int j = 0; j <= deg[u]; ++j) g[T][j] = 0;
			g[0][0] = 1;
			for (int i = 0; i <= deg[u]; ++i) {
				if (i > B || (i <= B && (S >> i & 1))) {
					h[0] = 1;
					for (int T = 1; T < alls; ++T) {
						int p = __builtin_ctz(T);
						h[T] = 1ll * h[T ^ (1 << p)] * suf[big[p]][i + 1] % Mod;
					}
					for (int T = 0; T < alls; ++T)
						for (int j = 0; j <= i; ++j)
							(dp[u][i] += 1ll * f[S] * (j & 1 ? Mod - 1 : 1) % Mod * pw[n - j][leaves] % Mod * g[T][j] % Mod * h[(alls - 1) ^ T] % Mod) %= Mod; 
				}
				for (int j = i; j >= 0; --j) {
					if (i > B || (i <= B && (S >> i & 1)))
						for (int T = 0; T < alls; ++T) (g[T][j + 1] += g[T][j]) %= Mod;
					// for (int T = 1; T < alls; ++T) {
						// int p = __builtin_ctz(T);
						// (g[T][j] += 1ll * g[T ^ (1 << p)][j] * dp[big[p]][i] % Mod) %= Mod;
					// }
					for (int k = 0; k < sz; ++k)
						for (int T = 0; T < alls; ++T)
							if (!(T >> k & 1)) (g[T | (1 << k)][j] += 1ll * g[T][j] * dp[big[k]][i] % Mod) %= Mod;
				}
			}
		}
		for (int i = n - 1; i >= 0; --i) (suf[u][i] = suf[u][i + 1] + dp[u][i]) %= Mod;
		while (dp[u][deg[u]] == 0) --deg[u];
	};
	DFS(0, -1);
	for (int i = 0; i <= n; ++i) std::cout << dp[0][i] << '\n';
	return 0;
}