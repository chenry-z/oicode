#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	std::vector<int> a(n), pos(n);
	std::vector<std::vector<int>> b(2, std::vector<int>(n));
	std::vector<std::vector<std::set<int>>> c(2, std::vector<std::set<int>>(n));
	for (auto &c : a) std::cin >> c, --c;
	for (auto &c : b[0]) std::cin >> c, --c;
	for (auto &c : b[1]) std::cin >> c, --c;
	for (int i = 0; i < n; ++i) {
		pos[a[i]] = i;
		c[0][b[0][i]].insert(i);
		c[1][b[1][i]].insert(i);
	}
	std::vector<bool> vis(n);
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		if (c[0][i].empty() || c[1][i].empty()) {
			std::function<void(int)> Del = [&](int x) {
				if (vis[x]) return;
				vis[x] = true;
				++ans;
				c[0][b[0][pos[x]]].erase(pos[x]);
				c[1][b[1][pos[x]]].erase(pos[x]);
				if (c[0][b[0][pos[x]]].empty()) Del(b[0][pos[x]]);
				if (c[1][b[1][pos[x]]].empty()) Del(b[1][pos[x]]);
			};
			Del(i);
		}
	}
	std::cout << ans << '\n';
	return 0;
}