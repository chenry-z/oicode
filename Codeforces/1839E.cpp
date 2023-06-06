#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) std::cin >> a[i];
	int sum = std::accumulate(a.begin(), a.end(), 0);
	std::vector dp(n + 1, std::vector<bool>(sum + 1));
	dp[0][0] = true;
	for (int i = 0; i < n; ++i) {
		dp[i + 1] = dp[i];
		for (int j = sum; j >= a[i]; --j) dp[i + 1][j] = dp[i][j] | dp[i][j - a[i]];
	}
	if (sum % 2 == 1 || !dp[n][sum / 2]) {
		std::cout << "First" << std::endl;
		while (true) {
			int mn = 999, pos = -1, x;
			for (int i = 0; i < n; ++i)
				if (a[i] > 0 && mn > a[i]) {
					mn = a[i], pos = i;
				}
			std::cout << pos + 1 << std::endl;
			std::cin >> x;
			if (x <= 0) return 0;
			a[x - 1] -= a[pos], a[pos] = 0;
		}
	} else {
		std::vector<bool> sep(n);
		for (int i = n - 1, u = sum / 2; i >= 0; --i) {
			if (u >= a[i] && dp[i][u - a[i]]) {
				u -= a[i];
				sep[i] = true;
			}
		}
		std::cout << "Second" << std::endl;
		for (int x, pos = -1;;) {
			std::cin >> x;
			if (x == -1) {
				for (auto c : a) std::cerr << c << ' ';
				return 0;
			}
			if (x-- <= 0) return 0;
			for (pos = 0; pos < n; ++pos)
				if (sep[x] != sep[pos] && a[pos] > 0) break;
			std::cout << pos + 1 << std::endl;
			int d = std::min(a[x], a[pos]);
			a[x] -= d, a[pos] -= d;
		}
	}
	return 0;
}