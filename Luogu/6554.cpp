#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	std::vector<std::vector<int>> e(n);
	std::vector<int> deg(n), a(n), sz(n);
	std::vector<long long> f(n);
	for (int i = 1, u, v; i < n; ++i) {
		std::cin >> u >> v;
		--u, --v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	int rt = -1;
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
		if (e[i].size() == 1ull) sz[i] = 1;
		else rt = i;
	}
	std::function<void(int, int)> DFS = [&](int u, int fa) {
		for (auto v : e[u]) {
			if (v == fa) continue;
			DFS(v, u);
			sz[u] += sz[v];
			f[u] += f[v];
		}
		f[u] += 1ll * sz[u] * a[u];
	};
	DFS(rt, -1);
	DFS = [&](int u, int fa) {
		for (auto v : e[u]) {
			if (v == fa) continue;
			if (e[v].size() == 1ull) f[v] = f[u] - a[u] + 1ll * a[v] * (sz[rt] - 2);
			else f[v] = f[u] - 1ll * a[u] * sz[v] + 1ll * a[v] * (sz[rt] - sz[v]);
			DFS(v, u);
		}
	};
	DFS(rt, -1);
	long double ans = -1E18;
	for (int i = 0; i < n; ++i) ans = std::max(ans, (long double)f[i] / (sz[rt] - (e[i].size() == 1ull)));
	std::cout << std::fixed << std::setprecision(9) << ans << '\n';
	return 0;
}