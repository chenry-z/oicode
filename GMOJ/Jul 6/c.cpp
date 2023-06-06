#include <bits/stdc++.h>
template<typename T = int>
class Fenwick {
	const int n;
	std::vector<T> a;
public:
	Fenwick(int n = 0) : n(n), a(n + 1) {}
	void Add(int x, const T &v) {for (; x <= n; x += x & -x) a[x] = std::max(a[x], v);}
	T Sum(int x) {
		T res = 0;
		for (; x; x -= x & (-x)) res = std::max(res, a[x]);
		return res;
	}
	void Clear(int x) {for (; x <= n; x += x & -x) a[x] = 0;}
};
int main() {
	freopen("a1.in", "r", stdin);
	freopen("a1.out", "w", stdout);
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	std::vector<int> fa(n), sz(n, 1), son(n, -1), a(n), ans(n, 1), f(n);
	std::vector<std::vector<int>> e(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> fa[i];
		fa[i]--;
		if (i != 0) e[fa[i]].emplace_back(i);
	}
	auto DFS = [&](auto self, int u) -> void {
		for (auto v : e[u]) {
			self(self, v);
			sz[u] += sz[v];
			if (son[u] == -1 || sz[son[u]] < sz[v]) son[u] = v;
		}
	};
	DFS(DFS, 0);
	for (auto &c : a) std::cin >> c;
	Fenwick<int> bit(n);
	auto Solve = [&](auto self, int u) -> void {
		auto DFS1 = [&](auto self, int u) -> void {
			bit.Clear(a[u]);
			for (auto v : e[u]) self(self, v);
		};
		for (auto v : e[u]) {
			if (v == son[u]) continue;
			self(self, v);
			ans[u] = std::max(ans[u], bit.Sum(a[u]) + 1);
			DFS1(DFS1, v);
		}
		if (son[u] != -1) self(self, son[u]);
		ans[u] = std::max(ans[u], bit.Sum(a[u]) + 1);
		auto DFS2 = [&](auto self, int u) -> void {
			bit.Add(a[u], ans[u]);
			for (auto v : e[u]) self(self, v);
		};
		bit.Add(a[u], ans[u]);
		for (auto v : e[u]) if (v != son[u]) DFS2(DFS2, v);
	};
	Solve(Solve, 0);
	for (int i = 0; i < n; ++i) std::cout << ans[i] << ' ';
	return 0;
}