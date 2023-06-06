#include <bits/stdc++.h>
using Info = std::array<int, 3>;
Info operator + (const Info &a, const Info &b) {
	return {
		a[0] + b[0],
		std::max(a[1], a[0] + b[1]),
		std::max(b[2], b[0] + a[2])
	};
}
Info operator + (const Info &a, const int &b) {
	return {a[0] + b, std::max(0, a[1] + b), std::max(0, a[2] + b)};
}
struct seg {
	std::vector<std::pair<Info, std::pair<int, int>>> val;
	void Build(int &x, int l, int r) {
		x = val.size();
		val.push_back({{r - l + 1, r - l + 1, r - l + 1}, {0, 0}});
		if (l == r) return;
		int m = (l + r) >> 1;
		Build(val[x].second.first, l, m);
		Build(val[x].second.second, m + 1, r);
	}
	void Modify(int &x, int l, int r, int p, int c, int pre) {
		x = val.size();
		val.push_back(val[pre]);
		if (l == r) return val[x].first = val[x].first + c, void();
		int m = (l + r) >> 1;
		auto &[ls, rs] = val[x].second;
		if (p <= m) Modify(ls, l, m, p, c, val[pre].second.first);
		else Modify(rs, m + 1, r, p, c, val[pre].second.second);
		val[x].first = val[ls].first + val[rs].first;
	}
	Info Query(int x, int l, int r, int L, int R) {
		if (L <= l && r <= R) return val[x].first;
		int m = (l + r) >> 1;
		Info res = val[0].first;
		if (L <= m) res = Query(val[x].second.first, l, m, L, R) + res;
		if (R > m) res = res + Query(val[x].second.second, m + 1, r, L, R);
		return res;
	}
	seg(int n) : val(1, {{0, -n, -n}, {0, 0}}) {val.reserve(n);}
} st(1E7);
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, q;
	std::cin >> n;
	std::vector<int> a(n), p(n);
	std::iota(p.begin(), p.end(), 0);
	for (int i = 0; i < n; ++i) std::cin >> a[i];
	std::sort(p.begin(), p.end(), [&](int x, int y) {return a[x] < a[y];});
	std::vector<int> rt(n);
	st.Build(rt[0], 1, n);
	for (int i = 1; i < n; ++i) st.Modify(rt[i], 1, n, p[i - 1] + 1, -2, rt[i - 1]);
	std::cin >> q;
	for (int ans = 0; q--;) {
		std::vector<int> f(4);
		for (auto &c : f) std::cin >> c, c = (c + ans) % n + 1;
		std::sort(f.begin(), f.end());
		auto Check = [&](int x) {
			int sm = st.Query(rt[x], 1, n, f[1], f[2])[0];
			int sl = st.Query(rt[x], 1, n, f[0], f[1] - 1)[2];
			int sr = st.Query(rt[x], 1, n, f[2] + 1, f[3])[1];
			return sm + sl + sr >= 0;
		};
		int l = 0, r = n - 1;
		while (l < r) {
			int m = (l + r + 1) >> 1;
			if (Check(m)) l = m;
			else r = m - 1;
		}
		std::cout << (ans = a[p[l]]) << '\n';
	}
	return 0;
}