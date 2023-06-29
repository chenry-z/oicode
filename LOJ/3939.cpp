#include <bits/stdc++.h>
struct sgt {
	std::vector<std::tuple<long long, int, int>> val;
	void Insert(int &x, int l, int r, int p, int q) {
		if (x == 0) {
			x = val.size();
			val.emplace_back(0, 0, 0);
		}
		auto &[sum, ls, rs] = val[x];
		sum += q;
		if (l == r) return;
		int m = (l + r) >> 1;
		if (p <= m) Insert(ls, l, m, p, q);
		else Insert(rs, m + 1, r, p, q);
	}
	int Query(int x, int l, int r, long long tot) {
		if (l == r) return l;
		auto [sum, ls, rs] = val[x];
		long long cur = std::get<0>(val[ls]);
		int m = (l + r) >> 1;
		if (cur >= tot) return Query(ls, l, m, tot);
		else return Query(rs, m + 1, r, tot - cur);
	}
	sgt(int n) {
		val.reserve(n);
		val.emplace_back(0, 0, 0);
	}
};
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, rt = 0;
	std::cin >> n;
	sgt st(n << 5);
	long long tot = 0;
	for (int i = 0, x, y; i < n; ++i) {
		std::cin >> x >> y;
		tot += y;
		st.Insert(rt, 1, 1E9, x, y);
		std::cout << st.Query(rt, 1, 1E9, (tot + 1) / 2) << '\n';
	}
	return 0;
}