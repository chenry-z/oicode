#include <bits/stdc++.h>
struct sgt {
	std::vector<std::tuple<int, int, int>> val;
	void Insert(int &x, int l, int r, int p) {
		val.emplace_back(0, 0, 0);
		if (x != 0) val.back() = val[x];
		x = val.size() - 1;
		auto &[sum, ls, rs] = val[x];
		++sum;
		if (l == r) return;
		int m = (l + r) >> 1;
		if (p <= m) Insert(ls, l, m, p);
		else Insert(rs, m + 1, r, p);
	}
	int Query(int u, int v, int l, int r, int p1, int p2) {
		auto [sumu, lsu, rsu] = val[u];
		auto [sumv, lsv, rsv] = val[v];
		int c1 = sumu + (l <= p1 && p1 <= r);
		int c2 = sumv + (l <= p2 && p2 <= r);
		if (c1 == 0 || c2 == 0 || l == r) return c1 - c2;
		int m = (l + r) >> 1;
		int cur = Query(rsu, rsv, m + 1, r, p1, p2);
		if (cur == 0) cur = Query(lsu, lsv, l, m, p1, p2);
		return cur;
	}
	sgt(int n) {
		val.reserve(n);
		val.emplace_back(0, 0, 0);
	}
};
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int T;
	std::cin >> T;
	while (T--) {
		int n, m;
		std::cin >> n >> m;
		std::vector<std::vector<std::pair<int, int>>> e(n);
		for (int i = 0, u, v, w; i < m; ++i) {
			std::cin >> u >> v >> w;
			--u, --v;
			e[u].emplace_back(v, w);
			e[v].emplace_back(u, w);
		}
		sgt st(n << 5);
		std::vector<int> rt(n);
		std::vector<bool> vis(n);
		std::vector<long long> dis(n, INT64_MAX);
		std::vector<std::pair<int, int>> pre(n);
		std::priority_queue<std::pair<long long, int>> q;
		dis[0] = 0;
		q.emplace(0, 0);
		while (q.size()) {
			auto [d, u] = q.top(); q.pop();
			if (vis[u]) continue;
			vis[u] = true;
			if (u != 0) st.Insert(rt[u] = rt[pre[u].first], 1, 5E4, pre[u].second);
			for (auto [v, w] : e[u])
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				pre[v] = {u, w};
				q.emplace(-dis[v], v);
			} else if (dis[v] == dis[u] + w) {
				if (st.Query(rt[pre[v].first], rt[u], 1, 5E4, pre[v].second, w) < 0) {
					pre[v] = {u, w};
				}
			}
		}
		std::vector<int> ans;
		for (int u = n - 1; u != 0; u = pre[u].first) ans.emplace_back(u);
		ans.emplace_back(0);
		std::reverse(ans.begin(), ans.end());
		std::cout << ans.size() << '\n';
		for (auto u : ans) std::cout << u + 1 << ' ';
		std::cout << '\n';
	}
	return 0;
}