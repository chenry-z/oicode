#include <bits/stdc++.h>
struct Tree {
	const int n;
	std::vector<std::vector<int>> e;
	std::vector<int> dfn, top, sz, son, dep, fa;
	void DFS(int u) {
		for (auto v : e[u]) {
			if (dep[v]) continue;
			fa[v] = u;
			dep[v] = dep[u] + 1;
			DFS(v);
			sz[u] += sz[v];
			if (son[u] == -1 || sz[son[u]] < sz[v]) son[u] = v;
		}
	}
	void HLD(int u, int t) {
		top[u] = t;
		static int dfx = 0;
		dfn[u] = ++dfx;
		if (son[u] == -1) return;
		HLD(son[u], t);
		for (auto v : e[u])
			if (v != fa[u] && v != son[u]) HLD(v, v);
	}
	Tree(int n) : n(n), e(n), dfn(n), top(n), sz(n, 1), son(n, -1), dep(n), fa(n) {
		for (int i = 1, u, v; i < n; ++i) {
			std::cin >> u >> v;
			--u, --v;
			e[u].emplace_back(v);
			e[v].emplace_back(u);
		}
		dep[0] = 1; DFS(0); HLD(0, 0);
	}
	int LCA(int x, int y) {
		if (x == -1) return y;
		if (y == -1) return x;
		for (; top[x] != top[y]; x = fa[top[x]])
			if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		return dep[x] < dep[y] ? x : y;
	}
	bool Sub(int x, int y) {
		return dfn[x] <= dfn[y] && dfn[y] < dfn[x] + sz[x];
	}
};
class Fenwick {
	const int n;
	std::vector<int> a;
	int _Sum(int x) {
		int res = 0;
		for (; x; x -= x & (-x)) res += a[x];
		return res;
	}
public:
	Fenwick(int n = 0) : n(n), a(n + 1) {}
	void Add(int x, const int &v) {for (; x <= n; x += x & -x) a[x] += v;}
	int Sum(int l, int r) {return _Sum(r) - _Sum(l - 1);}
};
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m, q;
	std::cin >> n >> m >> q;
	std::vector<std::vector<int>> e(n);
	Tree T(n);
	std::vector<int> a(m + 1), val(4 << std::__lg(m)), pre(m + 1), ans(q, 1);
	for (int i = 1; i <= m; ++i) std::cin >> a[i], --a[i];
	std::function<void(int, int, int)> Build = [&](int x, int l, int r) {
		if (l == r) return val[x] = a[l], void();
		int mid = (l + r) >> 1;
		Build(x << 1, l, mid), Build(x << 1 | 1, mid + 1, r);
		val[x] = T.LCA(val[x << 1], val[x << 1 | 1]);
	};
	Build(1, 1, m);
	auto Get = [m](int l, int r) {
		std::vector<std::tuple<int, int, int>> ans;
		std::function<void(int, int, int, int, int)> Split = [&](int x, int l, int r, int L, int R) {
			if (l > R || L > r) return;
			if (L <= l && r <= R) return ans.emplace_back(x, l, r), void();
			int mid = (l + r) >> 1;
			Split(x << 1, l, mid, L, R), Split(x << 1 | 1, mid + 1, r, L, R);
		};
		Split(1, 1, m, l, r);
		return ans;
	};
	for (int i = 1; i <= m; ++i) {
		auto cur = Get(1, i);
		std::reverse(cur.begin(), cur.end());
		for (int u = -1; auto [x, l, r] : cur) {
			if (T.Sub(a[i], T.LCA(val[x], u))) u = T.LCA(val[x], u), pre[i] = l;
			else {
				while (l < r) {
					if (T.Sub(a[i], T.LCA(u, val[x << 1 | 1])))
						u = T.LCA(u, val[x << 1 | 1]), x <<= 1, r = (l + r) >> 1;
					else l = ((l + r) >> 1) + 1, x = x << 1 | 1;
				}
				pre[i] = l + 1;
				break;
			}
		}
	}
	std::vector<std::vector<std::pair<int, int>>> Q(m + 1);
	for (int k, i = 0; i < q; ++i) {
		std::cin >> k;
		for (int L, R, u = -1; k--;) {
			std::cin >> L >> R;
			if (u == -1) u = a[L++];
			auto cur = Get(L, R);
			int v = -1, pt = L;
			for (auto [x, l, r] : cur) {
				if (!T.Sub(T.LCA(v, val[x]), u)) v = T.LCA(v, val[x]), pt = r + 1;
				else {
					while (l < r) {
						if (!T.Sub(T.LCA(v, val[x << 1]), u))
							v = T.LCA(v, val[x << 1]), x = x << 1 | 1, l = ((l + r) >> 1) + 1;
						else x <<= 1, r = (l + r) >> 1;
					}
					pt = l;
					break;
				}
			}
			for (auto [x, l, r] : cur) u = T.LCA(u, val[x]);
			Q[pt - 1].emplace_back(L, q + i);
			Q[R].emplace_back(L, i);
		}
	}
	Fenwick bit(m);
	for (int i = 1; i <= m; ++i)
		for (bit.Add(pre[i], 1); auto [L, id] : Q[i])
			id >= q ? ans[id - q] -= bit.Sum(1, L) : ans[id] += bit.Sum(1, L);
	for (auto c : ans) std::cout << c << '\n';
	return 0;
}