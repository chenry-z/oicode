#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	using u64 = unsigned long long;
	auto h = [](u64 x) {
		return x * x * x + x * 12 + 6;
	};
	auto has = [&](u64 x) {
		return h(x & ((1u << 31) - 1)) + h(x >> 31);
	};
	auto Get = [&](std::vector<std::vector<int>> e) {
		int n = e.size();
		std::vector<u64> f(n, 114);
		std::function<void(int, int)> DFS = [&](int u, int fa) -> void {
			for (auto v : e[u])
				if (v != fa) DFS(v, u), f[u] += has(f[v]);
		};
		DFS(0, -1);
		DFS = [&](int u, int fa) -> void {
			if (fa != -1) f[u] += has(f[fa] - has(f[u]));
			for (auto v : e[u])
				if (v != fa) DFS(v, u);
		};
		DFS(0, -1);
		return f;
	};
	int n;
	std::cin >> n;
	std::vector<std::vector<int>> e(n);
	for (int i = 1, u, v; i < n; ++i) {
		std::cin >> u >> v;
		--u, --v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	auto f = Get(e);
	e.assign(n + 1, {});
	for (int i = 0, u, v; i < n; ++i) {
		std::cin >> u >> v;
		--u, --v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	auto g = Get(e);
	std::set<u64> s;
	for (int i = 0; i < n; ++i) s.emplace(f[i]);
	int ans = n + 1;
	for (int u = 0; u <= n; ++u) {
		int mn = n + 1;
		for (auto v : e[u])
			if (e[v].size() == 1ull) mn = std::min(mn, v);
		if (mn != n + 1 && s.count(g[u] - has(114))) ans = std::min(ans, mn);
	}
	std::cout << ans + 1 << '\n';
	return 0;
}