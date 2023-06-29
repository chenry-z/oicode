#include <bits/stdc++.h>
struct RMQ {
	const int n;
	std::vector<int> lg;
	std::vector<std::vector<int>> val;
	RMQ(std::vector<int> a) : n(a.size() - 1), lg(n + 1) {
		lg[0] = -1;
		for (int i = 1; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
		val.assign(lg[n] + 1, std::vector<int>(n + 1));
		for (int i = 1; i <= n; ++i) val[0][i] = a[i];
		for (int i = 1; i <= lg[n]; ++i)
			for (int j = 1; j + (1 << i) - 1 <= n; ++j)
				val[i][j] = val[i - 1][j] & val[i - 1][j + (1 << (i - 1))];
	}
	int Query(int l, int r) {
		if (l > r) return (1 << 30) - 1;
		int sz = lg[r - l + 1];
		return val[sz][l] & val[sz][r - (1 << sz) + 1];
	}
};
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int T;
	std::cin >> T;
	while (T--) {
		int n;
		std::cin >> n;
		std::vector<int> a(n + 1);
		for (int i = 1; i <= n; ++i) std::cin >> a[i];
		RMQ st(a);
		int ans = 0;
		for (int k = 1; k < n; ++k) ans = std::max(ans, st.Query(1, k) + st.Query(k + 1, n));
		std::vector<int> pre, suf;
		for (int i = 1, cur = (1 << 30) - 1; i <= n; ++i)
			if ((cur & a[i]) != cur)
				pre.emplace_back(i), cur &= a[i];
		for (int i = n, cur = (1 << 30) - 1; i >= 1; --i)
			if ((cur & a[i]) != cur)
				suf.emplace_back(i), cur &= a[i];
		for (auto c1 : pre)
			for (auto c2 : suf)
				for (int k = c1; k < c2; ++k)
					ans = std::max(ans, (st.Query(1, c1 - 1) & st.Query(c1 + 1, k) & a[c2]) + (st.Query(k + 1, c2 - 1) & st.Query(c2 + 1, n) & a[c1]));
		std::map<int, std::vector<int>> f;
		for (int k = 1; k < n; ++k)
			for (auto c1 : pre) if (c1 <= k) {
				int val = st.Query(1, c1 - 1) & st.Query(c1 + 1, k);
				if (!f.count(val)) {
					auto &vec = f[val];
					vec.resize(n + 1);
					for (int i = n; i >= 1; --i) vec[i] = (i == n) ? (a[i] & val) : std::max(vec[i + 1], a[i] & val);
				}
				ans = std::max(ans, f[val][k + 1] + (st.Query(k + 1, n) & a[c1]));
			}
		f.clear();
		for (int k = 1; k < n; ++k)
			for (auto c2 : suf) if (c2 > k) {
				int val = st.Query(k + 1, c2 - 1) & st.Query(c2 + 1, n);
				if (!f.count(val)) {
					auto &vec = f[val];
					vec.resize(n + 1);
					for (int i = 1; i <= n; ++i) vec[i] = std::max(vec[i - 1], a[i] & val);
				}
				ans = std::max(ans, f[val][k] + (st.Query(1, k) & a[c2]));
			}
		std::cout << ans << '\n';
	}
	return 0;
}