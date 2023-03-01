#include <bits/stdc++.h>
struct Matrix {
	std::vector<std::vector<long long>> a;
	Matrix() : a(2, std::vector<long long>(2, -1E12)) {}
	Matrix operator+(const Matrix& b) const {
		Matrix c;
		c.a[0][0] = std::max(a[0][0] + b.a[0][0], a[0][1] + b.a[1][0]);
		c.a[1][0] = std::max(a[1][0] + b.a[0][0], a[1][1] + b.a[1][0]);
		c.a[0][1] = std::max(a[0][0] + b.a[0][1], a[0][1] + b.a[1][1]);
		c.a[1][1] = std::max(a[1][0] + b.a[0][1], a[1][1] + b.a[1][1]);
		return c;
	}
};
template<class Info, class Merge = std::plus<Info>>
class Seg {
	const int n;
	const Merge merge;
	std::vector<Info> val;
	void _Modify(int x, int l, int r, int p, const Info &v) {
		if (l == r) return val[x] = v, void();
		int m = (l + r) >> 1;
		if (p <= m) _Modify(x << 1, l, m, p, v);
		else _Modify(x << 1 | 1, m + 1, r, p, v);
		val[x] = merge(val[x << 1], val[x << 1 | 1]);
	}
	Info _Query(int x, int l, int r, int L, int R) {
		if (l > R || L > r) return Info();
		if (L <= l && r <= R) return val[x];
		int m = (l + r) >> 1;
		return merge(_Query(x << 1, l, m, L, R), _Query(x << 1 | 1, m + 1, r, L, R));
	}
public:
	Seg(int n) : n(n), merge(Merge()), val((4 << std::__lg(n)) + 1) {}
	void Modify(int p, const Info &v) {_Modify(1, 1, n, p, v);}
	Info Query(int l, int r) {return _Query(1, 1, n, l, r);}
};
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::string s;
	int n, m;
	std::cin >> n >> m >> s;
	std::vector<int> fa(n), sz(n, 1), son(n, -1), top(n), dfn(n), out(n);
	std::vector<long long> p(n);
	for (int i = 0; i < n; ++i) std::cin >> p[i];
	long long sum = std::accumulate(p.begin(), p.end(), 0ll);
	std::vector<std::vector<int>> e(n);
	std::vector<std::array<long long, 2>> f(n);
	std::vector<Matrix> mat(n);
	for (int i = 1, u, v; i < n; ++i) {
		std::cin >> u >> v;
		--u; --v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	auto DFS = [&](auto self, int u) -> void {
		mat[u].a[1][0] = f[u][1] = p[u];
		mat[u].a[0][0] = 0;
		for (int v : e[u]) if (v != fa[u]) {
			fa[v] = u;
			self(self, v);
			sz[u] += sz[v];
			f[u][1] += f[v][0];
			f[u][0] += std::max(f[v][0], f[v][1]);
			if (son[u] == -1 || sz[son[u]] < sz[v]) son[u] = v;
		}
	};
	auto HLD = [&](auto self, int u, int t) -> void {
		top[u] = t;
		static int cnt = 0;
		dfn[u] = ++cnt;
		out[t] = std::max(out[t], cnt);
		if (son[u] == -1) return;
		self(self, son[u], t);
		for (int v : e[u]) if (v != fa[u] && v != son[u]) {
			self(self, v, v);
			mat[u].a[0][0] += std::max(f[v][0], f[v][1]);
			mat[u].a[1][0] += f[v][0];
		}
		mat[u].a[0][1] = mat[u].a[0][0];
	};
	fa[0] = -1; DFS(DFS, 0), HLD(HLD, 0, 0);
	Seg<Matrix> st(n);
	for (int i = 0; i < n; ++i) st.Modify(dfn[i], mat[i]);
	auto pp = p;
	auto Modify = [&](int u, long long w) {
		mat[u].a[1][0] += w - p[u];
		p[u] = w;
		while (true) {
			auto pre = st.Query(dfn[top[u]], out[top[u]]);
			st.Modify(dfn[u], mat[u]);
			auto suf = st.Query(dfn[top[u]], out[top[u]]);
			u = fa[top[u]];
			if (u == -1) break;
			mat[u].a[0][0] += std::max(suf.a[1][0], suf.a[0][0]) - std::max(pre.a[1][0], pre.a[0][0]);
			mat[u].a[0][1] = mat[u].a[0][0];
			mat[u].a[1][0] += suf.a[0][0] - pre.a[0][0];
		}
	};
	for (int a, b, x, y; m--;) {
		std::cin >> a >> x >> b >> y;
		--a, --b;
		// if (x == 1) Modify(a, 1E12);
		// else Modify(a, -1E12);
		// if (y == 1) Modify(b, 1E12);
		// else Modify(b, -1E12);
		auto ans = st.Query(1, out[0]);
		std::cout << sum - std::max(ans.a[0][0], ans.a[1][0]) - (long long)1E12 * (x + y) << '\n';
		Modify(a, pp[a]);
		Modify(b, pp[b]);
	}
	return 0;
}