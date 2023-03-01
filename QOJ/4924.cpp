#include <bits/stdc++.h>
#define int long long
struct Line {
	int k;
	long long b;
	Line(int k = 0, long long b = 1ll << 61) : k(k), b(b) {}
	long long operator()(int x) {return 1ll * k * x + b;}
};
std::vector<int> rnk, top;
struct seg {
	std::vector<std::array<std::vector<Line>, 3>> val;
	std::vector<std::array<int, 3>> head;
	bool compare(const Line &a, const Line &b, const Line &c) {
		return (__int128)(c.b - a.b) * (b.k - c.k) >= (__int128)(c.b - b.b) * (a.k - c.k);
	}
	void Modify(int x, int l, int r, int p, const std::array<Line, 3> &w) {
		if (top[rnk[l]] == top[rnk[r]]) {
			for (int i = 0; i < 3; ++i) {
				while (val[x][i].size() >= 2ull && compare(val[x][i][val[x][i].size() - 2], val[x][i][val[x][i].size() - 1], w[i]))
					val[x][i].pop_back();
				val[x][i].emplace_back(w[i]);
			}
		}
		if (l == r) return;
		int m = (l + r) >> 1;
		if (p <= m) Modify(x << 1, l, m, p, w);
		else Modify(x << 1 | 1, m + 1, r, p, w);
	}
	long long Query(int x, int l, int r, int L, int R, int id, int k) {
		if (L > r || l > R) return 1ll << 61;
		if (L <= l && r <= R) {
			if (val[x][id].empty()) return 1ll << 61;
			while (head[x][id] + 1 < (int)val[x][id].size() && val[x][id][head[x][id]](k) > val[x][id][head[x][id] + 1](k)) ++head[x][id];
			return val[x][id][head[x][id]](k);
		}
		int m = (l + r) >> 1;
		return std::min(Query(x << 1, l, m, L, R, id, k), Query(x << 1 | 1, m + 1, r, L, R, id, k));
	}
	seg(int n) : val(4 << std::__lg(n)), head(4 << std::__lg(n)) {}
};
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m, q;
	std::cin >> n >> m >> q;
	std::vector<std::pair<int, int>> a(n);
	for (int i = 0, x; i < n; ++i) {
		std::cin >> x;
		a[i] = {x, i};
	}
	std::sort(a.rbegin(), a.rend());
	std::vector<std::vector<std::pair<int, long long>>> e(n);
	for (int i = 1, u, v; i < n; ++i) {
		long long w;
		std::cin >> u >> v >> w;
		--u, --v;
		e[u].emplace_back(v, w);
		e[v].emplace_back(u, w);
	}
	std::vector<int> sz(n, 1), son(n, -1), dep(n), fa(n, -1), dfn(n), ed(n);
	top.resize(n);
	rnk.resize(n + 1);
	std::vector<long long> dis(n, -1), Ans(q);
	std::function<void(int)> DFS = [&](int u) {
		for (auto [v, w] : e[u]) {
			if (dis[v] != -1) continue;
			fa[v] = u;
			dep[v] = dep[u] + 1;
			dis[v] = dis[u] + w;
			DFS(v);
			sz[u] += sz[v];
			if (son[u] == -1 || sz[son[u]] < sz[v]) son[u] = v;
		}
	};
	std::function<void(int, int)> HLD = [&](int u, int t) {
		static int dfx = 0;
		rnk[dfn[u] = ++dfx] = u;
		top[u] = t;	
		if (son[u] == -1) return ed[u] = u, void();
		ed[u] = ed[son[u]];
		HLD(son[u], t);
		for (auto [v, w] : e[u])
			if (v != fa[u] && v != son[u]) HLD(v, v);
	};
	dis[0] = 0, DFS(0), HLD(0, 0);
	seg st(n);
	for (auto [x, u] : a) {
		long long val = dis[u];
		for (; u != -1; u = fa[top[u]])
			st.Modify(1, 1, n, dfn[u], {Line(x, 2 * val - 2 * dis[u]), Line(x, 2 * val), Line(x, 2 * val - 4 * dis[u])});
	}
	std::vector<std::array<int, 4>> Q(q);
	for (int i = 0; i < q; ++i) {
		long long s, t;
		std::cin >> s >> t;
		--s, --t;
		Q[i] = {(int)std::abs(t / n - s / n), (int)s % n, (int)t % n, i};
	}
	std::sort(Q.begin(), Q.end());
	auto LCA = [&](int x, int y) {
		for (; top[x] != top[y]; x = fa[top[x]])
			if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		return dep[x] < dep[y] ? x : y;
	};
	for (auto [dif, x, y, id] : Q) {
		int l = LCA(x, y);
		long long ans = 1ll << 61, cur = dis[x] + dis[y] - 2 * dis[l];
		for (; top[x] != top[l]; x = fa[top[x]]) {
			ans = std::min(ans, st.Query(1, 1, n, dfn[top[x]], dfn[x], 0, dif));
			ans = std::min(ans, st.Query(1, 1, n, dfn[x], dfn[ed[x]], 1, dif) - 2 * dis[x]);
		}
		ans = std::min(ans, st.Query(1, 1, n, dfn[l], dfn[x], 0, dif));
		ans = std::min(ans, st.Query(1, 1, n, dfn[x], dfn[ed[x]], 1, dif) - 2 * dis[x]);
		for (; top[y] != top[l]; y = fa[top[y]]) {
			ans = std::min(ans, st.Query(1, 1, n, dfn[top[y]], dfn[y], 0, dif));
			ans = std::min(ans, st.Query(1, 1, n, dfn[y], dfn[ed[y]], 1, dif) - 2 * dis[y]);
		}
		ans = std::min(ans, st.Query(1, 1, n, dfn[l], dfn[y], 0, dif));
		ans = std::min(ans, st.Query(1, 1, n, dfn[y], dfn[ed[y]], 1, dif) - 2 * dis[y]);
		long long val = dis[l];
		for (; l != -1; l = fa[top[l]]) {
			ans = std::min(ans, st.Query(1, 1, n, dfn[top[l]], dfn[l], 2, dif) + 2 * val);
			ans = std::min(ans, st.Query(1, 1, n, dfn[l], dfn[ed[l]], 1, dif) + 2 * val - 4 * dis[l]);
		}
		Ans[id] = ans + cur;
	}
	for (auto c : Ans) std::cout << c << '\n';
	return 0;
}