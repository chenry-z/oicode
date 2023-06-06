#include <bits/stdc++.h>
#pragma GCC optimize(2)
int main() {
	freopen("c.in", "r", stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m;
	std::cin >> n >> m;
	std::vector<int> col(n), rnk(n * 2 + 1), in(n), out(n), sz(n, 1), dep(n), fa(n), son(n, -1), top(n), cnt(n + 1), ans(m);
	std::vector<std::vector<int>> e(n);
	for (auto &c : col) std::cin >> c;
	for (int i = 1, u, v; i <= n; ++i) {
		std::cin >> u >> v;
		--u; --v;
		if (u == -1 || v == -1) continue;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	int _ = 0;
	std::function<void(int)> DFS = [&](int u) {
		in[u] = ++_;
		rnk[_] = u;
		for (auto v : e[u]) {
			if (dep[v]) continue;
			dep[v] = dep[u] + 1;
			fa[v] = u;
			DFS(v);
			sz[u] += sz[v];
			if (son[u] == -1 || sz[son[u]] < sz[v]) son[u] = v;
		}
		out[u] = ++_;
		rnk[_] = u;
	};
	std::function<void(int, int)> HLD = [&](int u, int t) {
		top[u] = t;
		if (son[u] == -1) return;
		HLD(son[u], t);
		for (auto &v : e[u])
			if (v != son[u] && v != fa[u]) HLD(v, v);
	};
	dep[0] = 1; DFS(0); HLD(0, 0);
	auto LCA = [&](int u, int v) {
		for (; top[u] != top[v]; u = fa[top[u]])
			if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
		return dep[u] < dep[v] ? u : v;
	};
	std::vector<std::array<int, 5>> q(m);
	for (int i = 0, u, v, a, b; i < m; ++i) {
		std::cin >> u >> v >> a >> b;
		--u; --v;
		if (in[u] > in[v]) std::swap(u, v);
		if (LCA(u, v) == u) q[i] = {in[u], in[v], a, b, i};
		else q[i] = {out[u], in[v], a, b, i};
	}
	int szz = ceil(n / sqrt(m));
	using qq = std::array<int, 5>;
	std::sort(q.begin(), q.end(), [&](const qq &a, const qq &b) {
		if (a[0] / szz == b[0] / szz) {
			if ((a[0] / szz) & 1) return a[1] < b[1];
			return a[1] > b[1];
		}
		return a[0] < b[0];
	});
	int L = 1, R = 0, sum = 0;
	std::vector<bool> vis(n);
	auto Change = [&](int x) {
		if (vis[x]) {
			vis[x] = false;
			--cnt[col[x]];
			sum -= (cnt[col[x]] == 0);
		} else {
			vis[x] = true;
			++cnt[col[x]];
			sum += (cnt[col[x]] == 1);
		}
	};
	for (auto item : q) {
		int l = item[0], r = item[1], a = item[2], b = item[3], id = item[4];
		int u = rnk[l], v = rnk[r];
		while (R < r) Change(rnk[++R]);
		while (R > r) Change(rnk[R--]);
		while (L > l) Change(rnk[--L]);
		while (L < l) Change(rnk[L++]);
		int lca = LCA(u, v);
		if (lca != u && lca != v) Change(lca);
		if (cnt[a] && cnt[b] && a != b) ans[id] = sum - 1;
		else ans[id] = sum;
		if (lca != u && lca != v) Change(lca);
	}
	for (auto &c : ans) std::cout << c << '\n';
	return 0;
}