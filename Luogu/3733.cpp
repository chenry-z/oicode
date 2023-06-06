#include <bits/stdc++.h>
constexpr int N = 1000;
using Info = std::bitset<N>;
struct Line {
	std::vector<Info> f;
	Line() : f(N) {}
	int Insert(Info x) {
		for (int i = N - 1; i >= 0; --i)
		if (x[i]) {
			if (f[i].any()) x ^= f[i];
			else {
				f[i] = x;
				return i;
			}
		}
		return -1;
	}
	Info Query() {
		Info res;
		for (int i = N - 1; i >= 0; --i)
			if (f[i].any() && !res[i]) res ^= f[i];
		return res;
			
	}
} f;
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m, q;
	std::cin >> n >> m >> q;
	std::vector<std::vector<std::pair<int, Info>>> e(n);
	for (int i = 0, u, v; i < m; ++i) {
		Info w;
		std::cin >> u >> v >> w;
		--u, --v;
		e[u].emplace_back(v, w);
		e[v].emplace_back(u, w);
	}
	std::vector<Info> dis(n);
	std::vector<bool> vis(n);
	std::function<void(int)> DFS = [&](int u) {
		vis[u] = true;
		for (auto [v, w] : e[u]) {
			if (vis[v]) f.Insert(dis[u] ^ dis[v] ^ w);
			else {
				dis[v] = dis[u] ^ w;
				DFS(v);
			}
		}
	};
	DFS(0);
	using Edge = std::tuple<int, int, Info>;
	std::vector<std::vector<Edge>> Q(4 << std::__lg(q));
	std::function<void(int, int, int, int, int, const Edge&)> Modify = [&](int x, int l, int r, int L, int R, const Edge &k) {
		if (l > R || L > r) return;
		if (L <= l && r <= R) {
			Q[x].emplace_back(k);
			return;
		}
		int m = (l + r) >> 1;
		Modify(x << 1, l, m, L, R, k);
		Modify(x << 1 | 1, m + 1, r, L, R, k);
	};
	std::vector<std::tuple<int, int, Info, int>> train;
	vis.clear();
	for (int i = 1, x, y; i <= q; ++i) {
		std::string s;
		Info z;
		std::cin >> s >> x;
		if (s == "Add") {
			std::cin >> y >> z;
			--x, --y;
			train.emplace_back(x, y, z, i);
			vis.emplace_back(false);
		} else if (s == "Cancel") {
			--x;
			auto [u, v, w, l] = train[x];
			Modify(1, 1, q, l, i - 1, {u, v, w});
			vis[x] = true;
		} else {
			std::cin >> z;
			--x;
			auto &[u, v, w, l] = train[x];
			Modify(1, 1, q, l, i - 1, {u, v, w});
			w = z;
			l = i;
		}
	}
	for (int i = 0; i < (int)train.size(); ++i) {
		auto [u, v, w, l] = train[i];
		if (!vis[i])
			Modify(1, 1, q, l, q, {u, v, w});
	}
	std::stack<int> stk;
	std::function<void(int, int, int)> Solve = [&](int x, int l, int r) {
		if (l > r) return;
		int presz = stk.size();
		for (auto [u, v, w] : Q[x]) {
			int cur = f.Insert(dis[u] ^ dis[v] ^ w);
			if (cur != -1) stk.emplace(cur);
		}
		if (l == r) {
			Info ans = f.Query();
			for (int i = N - 1, flag = 0; i >= 0; --i) {
				if (ans[i] == 1) flag = 1;
				if (flag) std::cout << ans[i];
			}
			std::cout << '\n';
		} else {
			int m = (l + r) >> 1;
			Solve(x << 1, l, m);
			Solve(x << 1 | 1, m + 1, r);
		}
		while ((int)stk.size() > presz) {
			int u = stk.top();
			stk.pop();
			f.f[u].reset();
		}
	};
	Info ans = f.Query();
	for (int i = N - 1, flag = 0; i >= 0; --i) {
		if (ans[i] == 1) flag = 1;
		if (flag) std::cout << ans[i];
	}
	std::cout << '\n';
	Solve(1, 1, q);
	return 0;
}