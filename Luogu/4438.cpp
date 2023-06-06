#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	std::vector<int> ls(n - 1), rs(n - 1);
	for (int i = 0; i < n - 1; ++i) {
		std::cin >> ls[i] >> rs[i];
		if (ls[i] < 0) ls[i] = n - 1 - ls[i];
		if (rs[i] < 0) rs[i] = n - 1 - rs[i];
		--ls[i], --rs[i];
	}
	std::vector<int> a(2 * n - 1), b(2 * n - 1), c(2 * n - 1);
	for (int i = n - 1; i < 2 * n - 1; ++i) std::cin >> a[i] >> b[i] >> c[i];
	std::vector f(100, std::vector(42, std::vector(42, 0ll)));
	std::vector<int> dfn(n * 2 - 1);
	std::function<void(int, int, int, int)> DFS = [&](int u, int x, int y, int d) {
		dfn[u] = d;
		if (u >= n - 1) {
			for (int i = 0; i <= x; ++i)
				for (int j = 0; j <= y; ++j)
					f[dfn[u]][i][j] = 1ll * c[u] * (a[u] + i) * (b[u] + j);
			return;
		}
		DFS(ls[u], x + 1, y, d + 1);
		DFS(rs[u], x, y + 1, d + 2);
		for (int i = 0; i <= x; ++i)
			for (int j = 0; j <= y; ++j)
				f[dfn[u]][i][j] = std::min(f[dfn[ls[u]]][i + 1][j] + f[dfn[rs[u]]][i][j], f[dfn[ls[u]]][i][j] + f[dfn[rs[u]]][i][j + 1]);
			
	};
	DFS(0, 0, 0, 0);
	std::cout << f[0][0][0] << '\n';
	return 0;
}