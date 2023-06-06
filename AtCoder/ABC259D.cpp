#include <bits/stdc++.h>
#define int long long
struct DSU {
	std::vector<int> fa, sz;
	DSU(int n = 0) : fa(n + 1), sz(n + 1, 1) {std::iota(fa.begin(), fa.end(), 0);}
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
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, sx, sy, tx, ty;
	std::cin >> n >> sx >> sy >> tx >> ty;
	std::vector<std::array<int, 3>> a(n);
	for (auto &[x, y, r] : a) std::cin >> x >> y >> r;
	int c1 = -1, c2 = -1;
	for (int i = 0; i < n; ++i) {
		int x = a[i][0], y = a[i][1], r = a[i][2];
		if ((x - sx) * (x - sx) + (y - sy) * (y - sy) == r * r) c1 = i;
		if ((x - tx) * (x - tx) + (y - ty) * (y - ty) == r * r) c2 = i;
	}
	DSU dsu(n);
	for (int i = 0; i < n; ++i) {
		auto &[x, y, r] = a[i];
		for (int j = i + 1; j < n; ++j) {
			auto &[x2, y2, r2] = a[j];
			if ((x - x2) * (x - x2) + (y - y2) * (y - y2) <= (r + r2) * (r + r2) && (x - x2) * (x - x2) + (y - y2) * (y - y2) >= (r - r2) * (r - r2)) dsu.Merge(i, j);
		}
	}
	if (c1 == -1 || c2 == -1 || (!dsu.Same(c1, c2))) std::cout << "No\n";
	else std::cout << "Yes\n";
	return 0;
}