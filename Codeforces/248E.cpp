#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, q;
	std::cin >> n;
	std::vector<int> a(n);
	using f64 = long double;
	std::vector<std::vector<f64>> f(n);
	f64 ans = 0;
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
		f[i].resize(a[i] + 1);
		f[i][a[i]] = 1;
		ans += f[i][0];
	}
	auto b = a;
	std::cin >> q;
	std::vector<std::array<f64, 6>> C(q * 5 + 101);
	for (int i = 0; i <= q * 5 + 100; ++i) C[i][0] = 1;
	for (int i = 1; i <= q * 5 + 100; ++i)
		for (int j = 1; j <= std::min(i, 5); ++j)
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	for (int u, v, w; q--;) {
		std::cin >> u >> v >> w;
		--u, --v, ans -= f[u][0];
		std::vector<f64> g(b[u] + 1);
		for (int i = 0; i <= b[u]; ++i)
			for (int j = 0; j <= std::min(w, i); ++j) {
				if (f[u][i] == 0 || w - j > a[u] - i) continue;
				g[i - j] += f[u][i] * C[i][j] * C[a[u] - i][w - j] / C[a[u]][w];
			}
		f[u] = g, a[u] -= w, a[v] += w, ans += f[u][0];
		std::cout << std::fixed << std::setprecision(10) << ans << '\n';
	}
	return 0;
}