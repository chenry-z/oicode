#include <bits/stdc++.h>
struct Line {
	long long k, b;
	long long calc(int x) {return x * k + b;}
};
constexpr int MAXN = 200000;
int rt[MAXN];
struct LICHAO_SEGMENT_TREE {
#define mid ((l + r) >> 1)
	Line s[MAXN << 5];
	int ls[MAXN << 5], rs[MAXN << 5], tol;
	void insert(int &x, Line v, int l = 0, int r = 1e9) {
		if (!x) {
            x = ++tol;
            s[x] = v;
            return;
        }
		Line u = s[x];
		long long resu = u.calc(mid), resv = v.calc(mid);
		if (l == r) {
			if (resv > resu) s[x] = v;
			return;
		}
		if (u.k < v.k) {
			if (resv > resu) {
				s[x] = v;
				insert(ls[x], u, l, mid);
			} else insert(rs[x], u, mid + 1, r);
		} else if (u.k > v.k) {
			if (resv > resu) {
				s[x] = v;
				insert(rs[x], u, mid + 1, r);
			} else insert(ls[x], v, l, mid);
		}
		else if (v.b > u.b) s[x] = v;
	}
	long long query(int x, int p, int l = 0, int r = 1e9) {
		if (!x) return 0;
		return std::max(s[x].calc(p),
		p <= mid ? query(ls[x], p, l, mid) : query(rs[x], p, mid + 1, r));
	}
} st;
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(n);
	for (auto &c : a) std::cin >> c;
	using i64 = long long;
	std::vector<std::vector<i64>> dis(n, std::vector<i64>(n, (1ll << 60)));
	for (int i = 0; i < n; ++i) dis[i][i] = 0;
	for (int i = 0, u, v, w; i < m; ++i) {
		std::cin >> u >> v >> w;
		--u, --v;
		dis[u][v] = w;
	}
	for (int k = 0; k < n; ++k)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
	std::vector f(1 << n, std::vector(n, (1ll << 60)));
	std::vector sum(1 << n, 0ll);
	for (int i = 0; i < n; ++i) f[1 << i][i] = 0, sum[1 << i] = a[i];
	for (int S = 1; S < (1 << n); ++S) if (__builtin_popcount(S) != 1)
		for (int i = 0; i < n; ++i) if (S >> i & 1) {
			sum[S] += a[i];
			for (int j = 0; j < n; ++j) if (i != j && (S >> j & 1) && dis[i][j] != (1ll << 60))
				f[S][j] = std::min(f[S][j], f[S ^ (1 << j)][i] + dis[i][j] * sum[S ^ (1 << j)]);
		}
	for (int i = 0; i < n; ++i)
		for (int S = 0; S < (1 << n); ++S) if (S >> i & 1)
			st.insert(rt[i], {sum[S], -f[S][i]});
	int Q;
	std::cin >> Q;
	for (int s, e; Q--;) {
		std::cin >> s >> e;
		std::cout << st.query(rt[e - 1], s) << '\n';
	}
	return 0;
}