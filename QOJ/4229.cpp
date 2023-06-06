#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::vector pri{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (auto &c : a) std::cin >> c;
	int mx = std::max(n << 1, *std::max_element(a.begin(), a.end()));
	std::vector<std::vector<int>> e(n);
	for (int i = 1, u, v; i < n; ++i) {
		std::cin >> u >> v;
		--u, --v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	std::vector<int> val, lst(mx + 1);
	auto Get = [&](auto &&Get, int u, int i) -> void {
		if (u != 1 && u <= mx) val.emplace_back(u), lst[u] = i;
		else if (u > mx) return;
		for (int j = i + 1; j < (int)pri.size(); ++j)
			Get(Get, u * pri[j], j);
	};
	Get(Get, 1, -1);
	for (auto &c : a)
		for (auto p : pri)
			while (c / p / p * p * p == c) c /= p;
	int m = val.size();
	std::vector f(n, std::vector<int>(m, n << 1));
	auto DFS = [&](auto &&DFS, int u, int fa) -> void {
		for (int i = 0; i < m; ++i) f[u][i] = (a[u] == val[i]) ? 0 : val[i];
		for (auto v : e[u]) {
			if (v == fa) continue;
			DFS(DFS, v, u);
			std::vector<int> g(pri.size(), n << 1);
			for (int i = 0; i < m; ++i)
				for (int x = val[i]; x > 1; x /= pri[lst[x]]) g[lst[x]] = std::min(g[lst[x]], f[v][i]);
			for (int i = 0; i < m; ++i) {
				int mn = 2 * n;
				for (int x = val[i]; x > 1; x /= pri[lst[x]]) mn = std::min(g[lst[x]], mn);
				f[u][i] += mn;
			}
		}
	};
	DFS(DFS, 0, -1);
	std::cout << *std::min_element(f[0].begin(), f[0].end()) << '\n';
 	return 0;
}