#include <bits/stdc++.h>
struct DSU {
	std::vector<int> fa, sz, lst;
	DSU(int n = 0) : fa(n), sz(n, 1), lst(n) {std::iota(fa.begin(), fa.end(), 0);}
	int Find(int x) {
		while (x != fa[x]) x = fa[x] = fa[fa[x]];
		return x;
	}
	bool Same(int x, int y) {return Find(x) == Find(y);}
	bool Merge(int x, int y) {
		x = Find(x), y = Find(y);
		if (x == y) return false;
		if (sz[x] > sz[y]) std::swap(x, y);
		fa[x] = y;
		sz[y] += sz[x];
		return true;
	}
	int size(int x) {return sz[Find(x)];}
};
int main() {
	#define int long long
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int T;
	std::cin >> T;
	while (T--) {
		int n;
		std::cin >> n;
		std::vector<int> a(n + 1);
		std::vector<std::vector<int>> b(n + 1);
		for (int i = 1; i <= n; ++i) std::cin >> a[i], b[a[i]].emplace_back(i);
		long long m;
		std::cin >> m;
		DSU dsu(n + 1);
		for (int i = 1; i <= n; ++i) dsu.lst[i] = a[i];
		std::vector<int> sum(n + 1);
		for (int i = 0; i <= n; ++i) {
			for (auto c : b[i]) {
				if (c > 1 && a[c - 1] <= i) {
					sum[dsu.size(c - 1)] += i - dsu.lst[dsu.Find(c - 1)];
					dsu.Merge(c - 1, c);
					dsu.lst[dsu.Find(c)] = i;
				}
				if (c < n && a[c + 1] <= i) {
					sum[dsu.size(c + 1)] += i - dsu.lst[dsu.Find(c + 1)];
					dsu.Merge(c, c + 1);
					dsu.lst[dsu.Find(c)] = i;
				}
			}
		}
		for (int i = 1; i <= n; ++i)
			if (dsu.Find(i) == i) {
				sum[dsu.size(i)] += n - dsu.lst[dsu.Find(i)];
			}
		// for (int i = 1; i <= n; ++i) std::cerr << sum[i] << " \n"[i == n];
		long long ans = 0;
		for (int i = n; i >= 1; --i) {
			int l = 0, r = sum[i];
			while (l < r) {
				int mi = (l + r + 1) >> 1;
				if (mi * i <= m) l = mi;
				else r = mi - 1; 
			}
			ans += l * (i - 1);
			m -= l * i;
			if (m == 0) break;
			if (l != sum[i]) {
				ans += m - 1;
				break;
			}
		}
		std::cout << ans << '\n';
	}
	return 0;
}