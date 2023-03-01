#include <bits/stdc++.h>
class Fenwick {
	const int n;
	std::vector<int> a;
	int _Sum(int x) {
		int res = 0;
		for (; x; x -= x & (-x)) res ^= a[x];
		return res;
	}
public:
	Fenwick(int n = 0) : n(n), a(n + 1) {}
	void Add(int x, const int &v) {for (; x <= n; x += x & -x) a[x] ^= v;}
	int Sum(int l, int r) {return _Sum(r) ^ _Sum(l - 1);}
};
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m;
	std::cin >> n;
	std::vector<int> a(n + 1), sum(n + 1);
	for (int i = 1; i <= n; ++i) std::cin >> a[i], sum[i] = sum[i - 1] ^ a[i];
	auto b = a;
	std::sort(b.begin(), b.end());
	b.erase(std::unique(b.begin(), b.end()), b.end());
	for (int i = 1; i <= n; ++i) a[i] = std::lower_bound(b.begin(), b.end(), a[i]) - b.begin();
	std::cin >> m;
	std::vector<std::tuple<int, int, int>> q(m);
	std::vector<int> ans(m), pre(b.size());
	for (int i = 0, l, r; i < m; ++i) {
		std::cin >> l >> r;
		q[i] = {r, l, i};
	}
	std::sort(q.begin(), q.end());
	Fenwick bit(n);
	for (int i = 1; auto [r, l, id] : q) {
		for (; i <= r; ++i) {
			if (pre[a[i]] != 0) bit.Add(pre[a[i]], b[a[i]]);
			pre[a[i]] = i;
			bit.Add(i, b[a[i]]);
		}
		ans[id] = bit.Sum(l, r) ^ sum[r] ^ sum[l - 1];
	}
	for (auto c : ans) std::cout << c << '\n';
	return 0;
}