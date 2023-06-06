#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	const int N = 1E7;
	std::vector<int> pri, g(N + 1), vis(N + 1), gg(N + 1);
	g[1] = 0;
	for (int i = 2; i <= N; ++i) {
		if (!vis[i]) g[i] = 1, pri.push_back(i);
		for (auto p : pri) {
			if (i * p > N) break;
			vis[i * p] = true;
			if (i % p == 0) break;
			else g[i * p] = -g[i];
		}
	}
	for (int i = 2; i <= N; ++i) {
		if (g[i] != 0)
			for (long long j = i; j <= N; j = 1ll * j * i) gg[j] = g[i];
		gg[i] += gg[i - 1];
	}
	int T;
	std::cin >> T;
	for (int n, m; T--;) {
		std::cin >> n >> m;
		long long ans = 0;
		for (int x = 1, gx; x <= std::min(n, m); x = gx + 1) {
			gx = std::min(n / (n / x), m / (m / x));
			ans += 1ll * (gg[gx] - gg[x - 1]) * (n / x) * (m / x);
		}
		std::cout << ans << std::endl;
	}
	return 0;
}