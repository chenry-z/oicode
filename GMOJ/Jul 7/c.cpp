#include <bits/stdc++.h>
void Work() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(n - 1);
	for (auto &c : a) std::cin >> c;
	a.push_back(INT32_MAX);
	std::vector<std::vector<std::pair<int, int>>> e(n);
	std::vector<std::array<int, 3>> edge(m);
	for (auto &item : edge) {
		int &u = item[0], &v = item[1], &w = item[2];
		std::cin >> u >> v >> w;
		--u; --v;
		e[u].emplace_back(v, w);
		e[v].emplace_back(u, w);
	}
	auto Dij = [&](int s) {
		std::vector<long long> dis(n, INT64_MAX / 2);
		std::vector<bool> vis(n);
		std::priority_queue<std::pair<long long, int>> q;
		q.emplace(0, s);
		dis[s] = 0;
		while (q.size()) {
			int u = q.top().second; q.pop();
			if (vis[u]) continue;
			vis[u] = true;
			for (auto item : e[u]) {
				int v = item.first, w = item.second;
				if (dis[v] > dis[u] + w) {
					dis[v] = dis[u] + w;
					q.emplace(-dis[v], v);
				}
			}
		}
		return dis;
	};
	auto dis1 = Dij(0), dis2 = Dij(n - 1);
	std::vector<std::vector<std::array<int, 3>>> g(n);
	for (auto item : edge) {
		int u = item[0], v = item[1], w = item[2];
		if (dis1[u] + dis2[v] + w == dis1[n - 1]) {
			g[u].push_back({v, std::min(a[u], a[v]), (int)g[v].size()});
			g[v].push_back({u, 0, (int)g[u].size() - 1});
		}
		if (dis1[v] + dis2[u] + w == dis1[n - 1]) {
			g[v].push_back({u, std::min(a[u], a[v]), (int)g[u].size()});
			g[u].push_back({v, 0, (int)g[v].size() - 1});
		}
	}
	std::vector<int> dep;
	auto BFS = [&]() {
		dep.assign(n, -1);
		std::queue<int> q;
		q.push(0);
		dep[0] = 0;
		while (q.size()) {
			int u = q.front(); q.pop();
			for (auto item : g[u]) {
				int v = item[0], f = item[1];
				if (f > 0 && dep[v] == -1) {
					dep[v] = dep[u] + 1;
					q.push(v);
				}
			}
		}
		return dep[n - 1] != -1;
	};
	auto DFS = [&](auto self, int u, int a) -> int {
		if (u == n - 1 || a == 0) return a;
		int flow = 0;
		for (auto &item : g[u]) {
			int v = item[0], f = item[1], rev = item[2];
			if (dep[v] != dep[u] + 1) continue;
			int ff = self(self, v, std::min(f, a));
			if (ff <= 0) continue;
			flow += ff;
			item[1] -= ff;
			g[v][rev][1] += ff;
			a -= ff;
			if (a == 0) break;
		}
		return flow;
	};
	long long ans = 0;
	while (BFS()) ans += DFS(DFS, 0, INT32_MAX);
	std::vector<int> col(n);
	long long sum = 0;
	auto Check = [&](auto self, int u, int c) -> void {
		col[u] = c;
		for (auto item : g[u]) {
			int v = item[0], f = item[1], rev = item[2];
			if (col[v] == 0 && c == 1 && f > 0) self(self, v, c);
			if (col[v] == 0 && c == 2 && g[v][rev][1] > 0) self(self, v, c);
		}
	};
	Check(Check, 0, 1), Check(Check, n - 1, 2);
	for (int u = 0; u < n; ++u)
		for (auto item : g[u])
			if (col[u] > 0 && col[item[0]] > 0 && col[u] != col[item[0]]) {
				if (a[u] == a[item[0]]) {
					std::cout << "No " << ans << std::endl;
					return;
				}
				sum += std::min(a[u], a[item[0]]);
			}
	std::cout << (sum / 2 == ans ? "Yes " : "No ") << ans << std::endl;
}
signed main() {
	std::ios::sync_with_stdio(false);
	int T;
	std::cin >> T;
	while (T--) Work();
	return 0;
}