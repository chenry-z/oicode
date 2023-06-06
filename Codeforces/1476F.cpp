#include <bits/stdc++.h>
struct seg {
	std::vector<int> val;
	void Modify(int x, int l, int r, int p, int v) {
		if (l == r) return val[x] = v, void();
		int m = (l + r) >> 1;
		if (p <= m) Modify(x << 1, l, m, p, v);
		else Modify(x << 1 | 1, m + 1, r, p, v);
		val[x] = std::max(val[x << 1], val[x << 1 | 1]);
	}
	int Query(int x, int l, int r, int L, int R) {
		if (l > R || L > r || l > r) return 0;
		if (L <= l && r <= R) return val[x];
		int m = (l + r) >> 1;
		return std::max(Query(x << 1, l, m, L, R), Query(x << 1 | 1, m + 1, r, L, R));
	}
	seg(int n) : val(4 << std::__lg(n)) {}
};
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int T;
	std::cin >> T;
	while (T--) {
		int n;
		std::cin >> n;
		std::vector<int> p(n + 1);
		for (int i = 1; i <= n; ++i) std::cin >> p[i];
		seg st(n);
		for (int i = 1; i <= n; ++i) st.Modify(1, 1, n, i, i + p[i]);
		std::vector<int> f(n + 1), pre(n + 1);
		pre[1] = 1;
		for (int i = 2; i <= n; ++i) {
			if (p[i] == 0) {
				f[i] = f[i - 1];
				pre[i] = i;
				continue;
			}
			// i to left, f[t] >= i - p[i] - 1
			int t = std::lower_bound(f.begin(), f.begin() + i, i - p[i] - 1) - f.begin();
			if (t == i) {
				// not valid, ignore
				f[i] = f[i - 1];
				pre[i] = i;
				continue;
			}
			pre[i] = t;
			f[i] = std::max(i - 1, st.Query(1, 1, n, t + 1, i - 1));
			// f[i - 1] -> f[i] ? ignore
			if (f[i - 1] > f[i]) {
				f[i] = f[i - 1];
				pre[i] = i;
			}
			// f[i - 1] >= i, i to right
			if (f[i - 1] >= i && i + p[i] > f[i]) {
				f[i] = i + p[i];
				pre[i] = i;
			}
		}
		if (f[n] < n) {
			std::cout << "NO\n";
			continue;
		}
		std::cout << "YES\n";
		std::string ans(n + 1, 'R');
		for (int u = n; u != 0;) {
			if (u == pre[u]) --u;
			else {
				ans[u] = 'L';
				u = pre[u];
			}
		}
		std::cout << ans.substr(1) << '\n';
	}
	return 0;
}