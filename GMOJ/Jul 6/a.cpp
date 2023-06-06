#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m, k;
	std::cin >> n >> m >> k;
	std::vector<std::vector<std::pair<int, int>>> e(n);
	std::vector<std::vector<int>> d(n, std::vector<int>(n, -1));
	for (int u, v, w; m--;) {
		std::cin >> u >> v >> w;
		--u; --v;
		e[u].emplace_back(v, w);
		d[u][v] = w;
	}
	std::vector<std::vector<bool>> a(n, std::vector<bool>(n));
	auto BFS = [&](int s) {
		std::queue<int> q;
		q.push(s);
		std::vector<bool> vis(n);
		while (q.size()) {
			int u = q.front(); q.pop();
			if (vis[u]) continue;
			vis[u] = true;
			for (auto item : e[u]) {
				int v = item.first;
				a[s][v] = true;
				q.push(v);
			}
		}
	};
	for (int i = 0; i < n; ++i) BFS(i);
	std::vector<std::vector<std::pair<int, int>>> g(n * (k + 1));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (d[i][j] == -1) continue;
			if (a[j][i]) for (int kk = 0; kk <= k; ++kk) 
				g[kk * n + i].emplace_back(kk * n + j, d[i][j]);
			else for (int kk = 0; kk < k; ++kk)
				g[kk * n + i].emplace_back((kk + 1) * n + j, d[i][j] * 2);
		}
	}
	std::vector<int> ans(n * (k + 1), INT32_MAX / 2);
	std::vector<bool> vis(n * (k + 1));
	std::priority_queue<std::pair<int, int>> q;
	q.emplace(0, 0);
	ans[0] = 0;
	while (q.size()) {
		int u = q.top().second; q.pop();
		if (vis[u]) continue;
		vis[u] = true;
		for (auto item : g[u]) {
			int v = item.first, w = item.second;
			if (ans[v] > ans[u] + w) {
				ans[v] = ans[u] + w;
				q.emplace(-ans[v], v);
			}
		}
	}
	int ret = INT32_MAX / 2;
	for (int i = 0; i <= k; ++i) ret = std::min(ret, ans[i * n + n - 1]);
	if (ret >= INT32_MAX / 2) std::cout << -1 << std::endl;
	else std::cout << ret << std::endl;
	return 0;
}