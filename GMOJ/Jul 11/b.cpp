#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	std::vector<std::array<int, 3>> a(n);
	for (auto &item : a) std::cin >> item[0] >> item[1] >> item[2];
	std::sort(a.begin(), a.end());
	std::vector<int> pos(n);
	for (int i = 0, cur = 0; i < n; ++i, ++cur) {
		pos[i] = cur = std::max(cur, a[i][0]);
	}
	std::sort(a.begin(), a.end(), [](auto x, auto y) { return x[2] > y[2]; });
	std::vector<int> vis(n, -1);
	auto Check = [&](auto self, int id, int p) -> bool {
		if (pos[p] > a[id][1]) return false;
		if (vis[p] == -1) {
			vis[p] = id;
			return true;
		}
		if (self(self, a[vis[p]][1] > a[id][1] ? vis[p] : id, p + 1)) {
			vis[p] = a[vis[p]][1] > a[id][1] ? id : vis[p];
			return true;
		}
		return false;
	};
	long long ans = 0;
	for (int i = 0; i < n; ++i) {
		int cur = 0;
		while (pos[cur] < a[i][0]) ++cur;
		if (Check(Check, i, cur)) ans += a[i][2];
	}
	std::cout << ans << std::endl;
	return 0;
}