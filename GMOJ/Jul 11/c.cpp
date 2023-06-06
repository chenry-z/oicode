#include <bits/stdc++.h>
#pragma GCC optimize(2)
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m;
	std::cin >> n >> m;
	std::vector<std::string> s(n);
	for (auto &str : s) std::cin >> str;
	std::vector<std::vector<int>> e(n + 1);
	std::vector<int> in(n);
	for (int i = 0; i < n; ++i) {
		int mx = -1, v = -1;
		for (int j = 0; j < n; ++j) {
			if (i != j && s[j] == s[i].substr(0, s[j].size())) {
				if ((int)s[j].size() > mx) {
					mx = s[j].size();
					v = j;
				}
			}
		}
		if (v != -1) e[i].push_back(v), ++in[v];
	}
	for (int i = 0; i < n; ++i)
		if (in[i] == 0) e[n].push_back(i);
	std::vector<int> sg(n + 1);
	std::string ans;
	for (int i = 0; i < n; ++i) {
		auto DFS = [&](auto self, int u) -> void {
			if (u == i) return;
			int cur = 0;
			for (auto &v : e[u]) {
				if (v == i) continue;
				self(self, v);
				cur ^= (sg[v] + 1);
			}
			sg[u] = cur;
		};
		DFS(DFS, n);
		if (sg[n] == 0) ans += s[i];
	}
	if (ans == "") std::cout << "Can’t win at all!!\n";
	else {
		for (int i = 0; i < ((int)ans.size() + 49) / 50; ++i) {
			for (int j = 0; j < 50; ++j) {
				if (i * 50 + j >= (int)ans.size()) break;
				std::cout << ans[i * 50 + j];
			}
			std::cout << '\n';
		}
	}
	return 0;
}