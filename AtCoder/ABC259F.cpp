#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	std::vector<int> d(n);
	std::vector<std::vector<std::pair<int, int>>> e(n);
	for (auto &c : d) std::cin >> c;
	for (int i = 1, u, v, w; i < n; ++i) {
		std::cin >> u >> v >> w;
		--u; --v;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}
	std::vector<std::array<int, 2>> f(n);
	auto DP = [&](auto self, int u, int fa) -> void {
		std::vector<int> ff;
		for (auto &[v, w] : e[u]) {
			if (v == fa) continue;
			self(self, v, u);
			ff.push_back(f[v][0] + w - f[v][1]);
			f[u][0] += f[v][1];
			f[u][1] += f[v][1];
		}
		std::sort(ff.rbegin(), ff.rend());
		for (int i = 0; i < (int)ff.size(); ++i) {
			if (ff[i] <= 0) break;
			if (i < d[u] - 1) f[u][0] += ff[i];
			if (i < d[u]) f[u][1] += ff[i];
		}
		if (d[u] == 0) f[u][0] = INT32_MIN / 2;
	};
	DP(DP, 0, -1);
	std::cout << *std::max_element(f[0].begin(), f[0].end());
	return 0;
}