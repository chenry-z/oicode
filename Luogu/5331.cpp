#include <bits/stdc++.h>
#include "atcoder/mincostflow"
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, w;
	std::cin >> n >> w;
	std::vector<int> a(n);
	for (auto &c : a) std::cin >> c;
	atcoder::mcf_graph<int, long long> g(2 * n + 2);
	int S = 2 * n, T = 2 * n + 1;
	for (int i = 0; i < n; ++i) {
		g.add_edge(S, i, 1, 0);
		g.add_edge(i + n, T, 1, 0);
		g.add_edge(i, T, 1, w);
	}
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < i - 1; ++j)
			if (std::abs(a[i] - a[j]) < w) g.add_edge(i, j + n, 1, std::abs(a[i] - a[j]));
	std::cout << g.flow(S, T).second << '\n';
	return 0;
} // brute force solution