#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	std::vector<std::vector<int>> e(n);
	for (int i = 0; i < n; ++i) std::cin >> a[i];
	for (int i = 1, u, v; i < n; ++i) {
		std::cin >> u >> v;
		--u, --v;
		e[u].emplace_back(v);
	}
	std::vector<long double> f(n);
	std::function<void(int, long double)> DFS = [&](int u, long double s) {
		f[u] = s + std::log(a[u]);
		for (auto v : e[u]) DFS(v, s + std::log(e[u].size()));
	};
	DFS(0, 0);
	std::sort(f.begin(), f.end());
	int ans = 0;
	for (int i = 1, x = 1; i < n; ++i)
		if (f[i] - f[i - 1] < 1E-8) ans = std::max(ans, ++x);
		else x = 1;
	std::cout << n - ans << '\n';
	return 0;
}