#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int T;
	std::cin >> T;
	while (T--) {
		int N, K;
		long long L, R;
		std::cin >> N >> K >> L >> R;
		std::vector<long long> a(N);
		for (int i = 0; i < N; ++i) std::cin >> a[i];
		std::vector<std::vector<int>> e(N);
		for (int i = 1, u, v; i < N; ++i) {
			std::cin >> u >> v;
			--u, --v;
			e[u].emplace_back(v);
			e[v].emplace_back(u);
		}
		std::vector f(N, std::vector(K + 1, std::vector<long long>()));
		std::vector<int> sz(N, 1);
		auto DFS = [&](auto &&DFS, int u, int fa) -> void {
			f[u][0].emplace_back(a[u]);
			for (auto v : e[u]) {
				if (v == fa) continue;
				DFS(DFS, v, u);
				std::vector<std::vector<long long>> g(K + 1);
				for (int i = 0; i <= std::min(sz[u] - 1, K); ++i)
					for (int j = 0; j <= std::min(sz[v] - 1, K - i); ++j)
						for (auto x : f[u][i]) {
							bool flag = false;
							for (auto y : f[v][j]) {
								if (x + y <= R) g[i + j].emplace_back(x + y);
								if (L <= y && y <= R) flag = true;
							}
							if (flag && i + j + 1 <= K) g[i + j + 1].emplace_back(x);
						}
				sz[u] += sz[v];
				for (int i = 0; i <= std::min(sz[u] - 1, K); ++i) {
					std::sort(g[i].begin(), g[i].end());
					f[u][i].clear();
					for (auto x : g[i]) {
						while (f[u][i].size() > 1ull && x - *std::prev(f[u][i].end(), 2) < R - L) f[u][i].pop_back();
						f[u][i].emplace_back(x);
					}
				}
			}
		};
		DFS(DFS, 0, -1);
		for (int i = 0; i <= K; ++i) {
			bool flag = false;
			for (auto x : f[0][i]) flag |= (L <= x && x <= R);
			std::cout << (flag ? '1' : '0');
		}
		std::cout << '\n';
	}
	return 0;
}