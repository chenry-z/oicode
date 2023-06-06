#include <bits/stdc++.h>
void Work() {
	int n;
	std::cin >> n;
	std::vector<int> col(n);
	for (int i = 0; i < n; ++i) std::cin >> col[i];
	std::vector<std::vector<std::pair<int, int>>> e(n);
	for (int i = 1, u, v, w; i < n; ++i) {
		std::cin >> u >> v >> w;
		--u; --v;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}
	std::vector<long long> f(n), g(n), h(n);
	auto DP = [&](auto self, int u, int fa) -> void {
		bool flag = false;
		long long cur = 0, mn = INT64_MAX;
		for (auto item : e[u]) {
			int v = item.first, w = item.second;
			if (v == fa) continue;
			flag = true;
			self(self, v, u);
			if (col[u] == 0) {
				g[u] += std::min({f[v] + w, g[v], h[v] + w});
				cur += std::min({f[v] + w, g[v], h[v] + w});
				mn = std::min(mn, h[v] - std::min({f[v] + w, g[v], h[v] + w}));
			} else if (col[u] == 1) {
				f[u] += std::min({f[v], g[v] + w, h[v] + w});
				h[u] += std::min({f[v] + w, g[v], h[v] + w});
			} else if (col[u] == 2) {
				f[u] += std::min({f[v], g[v] + w, h[v] + w});
				g[u] += std::min({f[v] + w, g[v], h[v] + w});
				cur += std::min({f[v] + w, g[v], h[v] + w});
				mn = std::min(mn, h[v] - std::min({f[v] + w, g[v], h[v] + w}));
			}
		}
		if (!flag) {
			if (col[u] == 0) f[u] = INT64_MAX / 2, g[u] = h[u] = 0;
			else if (col[u] == 1) f[u] = h[u] = 0, g[u] = INT64_MAX / 2;
			else if (col[u] == 2) f[u] = g[u] = h[u] = 0;
		} else {
			if (col[u] == 0) f[u] = INT64_MAX / 2, h[u] = cur + mn;
			else if (col[u] == 1) g[u] = INT64_MAX / 2;
			else if (col[u] == 2) h[u] = cur + mn;
		}
	};
	DP(DP, 0, -1);
	std::cout << std::min({f[0], g[0], h[0]}) << std::endl;
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int T;
	std::cin >> T;
	while (T--) Work();
	return 0;
}