#include <bits/stdc++.h>
#pragma GCC optimize(2)
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	std::vector<std::pair<int, int>> a(n);
	for (auto &c : a) std::cin >> c.first >> c.second;
	int ans1 = 0, ans2 = INT32_MAX;
	for (int i = 0; i < n - 2; ++i)
		for (int j = i + 1; j < n - 1; ++j)
			for (int k = j + 1; k < n; ++k) {
				int x1 = a[i].first, y1 = a[i].second;
				int x2 = a[j].first, y2 = a[j].second;
				int x3 = a[k].first, y3 = a[k].second;
				ans1 = std::max(ans1, std::abs(x1 - x2) + std::abs(x1 - x3) + std::abs(x2 - x3)
									+ std::abs(y1 - y2) + std::abs(y1 - y3) + std::abs(y2 - y3));
				ans2 = std::min(ans2, std::abs(x1 - x2) + std::abs(x1 - x3) + std::abs(x2 - x3)
									+ std::abs(y1 - y2) + std::abs(y1 - y3) + std::abs(y2 - y3));
			}
	std::cout << ans1 << '\n' << ans2 << '\n';
	return 0;
}